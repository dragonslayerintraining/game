#include "compiler.hpp"
#include "../val/val.hpp"
#include "../val/matcher.hpp"
#include "../val/summarize.hpp"
#include "finalizelabels.hpp"
#include "exception.hpp"

#include <iostream>

namespace lisp{
  namespace compiler{
    ccompiler::ccompiler(environ::cenvironptr environ,
			 errlog::cerrlogptr errlog):
      environ(environ),errlog(errlog),symtab(environ){
    }
    std::ostream& ccompiler::error(val::cvalptr where){
      struct val::csummarizevisitor summarize;
      where->accept(summarize);
      return errlog->error()<<"In '"<<summarize.getstr()<<"':"<<std::endl<<"\t";
    }
    void ccompiler::enterscope(int numvars,bytecode::cbytecodeptr code){
      symtab.pushscope();
      if(numvars>0){
	code->append(new bytecode::instr::creservelocal(numvars));
      }
    }
    void ccompiler::exitscope(int numvars,bytecode::cbytecodeptr code){
      if(numvars>0){
	code->append(new bytecode::instr::cfreelocal(numvars));
      }
      symtab.popscope();
    }
    bool ccompiler::loadvar(std::string name,bytecode::cbytecodeptr code,
			    val::cvalptr where){
      try{
	int id=symtab.locals->findvar(name);
	code->append(new bytecode::instr::cloadlocal(id));
	return true;
      }catch(const exception::undeclared_variable& e){
	try{
	  int id=symtab.globals->findvar(name);
	  code->append(new bytecode::instr::cloadglobal(id));
	  return true;
	}catch(const exception::undeclared_variable& e){
	  error(where)<<"Variable '"<<e.name<<"' is undeclared"<<std::endl;
	  return false;
	}
      }
    }
    bool ccompiler::storevar(std::string name,bytecode::cbytecodeptr code,
			    val::cvalptr where){
      try{
	int id=symtab.locals->findvar(name);
	code->append(new bytecode::instr::cstorelocal(id));
	return true;
      }catch(const exception::undeclared_variable& e){
	try{
	  int id=symtab.globals->findvar(name);
	  code->append(new bytecode::instr::cstoreglobal(id));
	  return true;
	}catch(const exception::undeclared_variable& e){
	  error(where)<<"Variable '"<<e.name<<"' is undeclared"<<std::endl;
	  return false;
	}
      }
    }
    void ccompiler::compileglobal(val::cvalptr expr){
      using namespace val::matcher;
      std::vector<val::cvalptr> list;
      if(!canylistmatcher(list).matches(expr)){
	error(expr)<<"Stray constant in program"<<std::endl;
      }
      if(list.size()==0){
	error(expr)<<"Global nil list"<<std::endl;
      }
      if(cidentmatcher("defvar").matches(list[0])){
	if(list.size()!=2){
	  error(expr)<<"'defvar' must take one parameter"<<std::endl;
	  return;
	}
	std::string varname;
	if(!canyidentmatcher(varname).matches(list[1])){
	  error(expr)<<"'defvar' must be followed by identifier"<<std::endl;
	  return;
	}
	try{
	  symtab.globals->declvar(varname);
	}catch(const exception::redeclared_variable& e){
	  error(expr)<<"Variable '"<<e.name<<"' redeclared"<<std::endl;
	}
	return;
      }
      if(cidentmatcher("defun").matches(list[0])){
	if(list.size()<4){
	  error(expr)<<"'defun' must take at least three parameters"<<std::endl;
	  return;
	}
	std::string funcname;
	if(!canyidentmatcher(funcname).matches(list[1])){
	  error(expr)<<"'defun' must be followed by"
		     <<" an identifier"<<std::endl;
	  return;
	}
	std::vector<val::cvalptr> params;
	if(!canylistmatcher(params).matches(list[2])){
	  error(expr)<<"'defun' must be followed by"
		     <<" an argument list"<<std::endl;
	  return;
	}
	try{
	  symtab.rsrvfunc(funcname,params.size());
	}catch(const exception::mismatched_arguments& e){
	  errlog->error()<<"Before definition, function '"<<e.name<<"'"
			<<" was called with "<<e.nargs1<<" parameters,"
			<<" but only takes "<<e.nargs2<<std::endl;
	  return;
	}
	bytecode::cbytecodeptr code=new bytecode::cbytecode();

	enterscope(params.size(),code);
	for(int i=params.size()-1;i>=0;i--){
	  std::string name;
	  if(!canyidentmatcher(name).matches(params[i])){
	    error(expr)<<"Argument names must be identifiers"<<std::endl;
	    symtab.popscope();
	    return;
	  }
	  try{
	    int id=symtab.locals->declvar(name);
	    code->append(new bytecode::instr::cstorelocal(id));
	  }catch(const exception::redeclared_variable& e){
	    //shouldn't happen
	    error(expr)<<"Variable '"<<e.name<<"' redeclared"<<std::endl;
	    return;
	  }
	}
	for(unsigned int i=3;i<list.size()-1;i++){
	  compileexpr(list[i],code);
	  code->append(new bytecode::instr::cpop());
	}
	compileexpr(list[list.size()-1],code);
	exitscope(params.size(),code);
	try{
	  code=finalizelabels(code);
	  //std::cerr<<"Function: "<<funcname<<std::endl;
	  //code->dump();
	  symtab.declfunc(funcname,params.size(),code);
	}catch(const exception::mismatched_arguments& e){
	  errlog->error()<<"Before definition, function '"<<e.name<<"'"
			<<" was called with "<<e.nargs1<<" parameters,"
			<<" but only takes "<<e.nargs2<<std::endl;
	}catch(const exception::redeclared_function& e){
	  errlog->error()<<"Function '"<<e.name<<"' redeclared"<<std::endl;
	}
      }else{
	error(expr)<<"Global expression is ill-formed"<<std::endl;
      }
    }
    void ccompiler::compileexpr(val::cvalptr expr,
				bytecode::cbytecodeptr code){
      using namespace val::matcher;
      std::vector<val::cvalptr> list;
      if((!canylistmatcher(list).matches(expr))||list.empty()){
	std::string ident;
	if(canyidentmatcher(ident).matches(expr)){
	  loadvar(ident,code,expr);
	  return;
	}
	code->append(new bytecode::instr::cconst(expr));
	return;
      }
      if(cidentmatcher("quote").matches(list[0])){
	if(list.size()!=2){
	  error(expr)<<"'quote' takes one arguments"<<std::endl;
	  return;
	}
	code->append(new bytecode::instr::cconst(list[1]));
	return;
      }else if(cidentmatcher("if").matches(list[0])){
	if(list.size()==3){
	  int label1=code->newlabel();
	  int label2=code->newlabel();
	  compileexpr(list[1],code);
	  code->append(new bytecode::instr::cjz(label1));
	  compileexpr(list[2],code);
	  code->append(new bytecode::instr::cjump(label2));
	  code->placelabel(label1);
	  code->append(new bytecode::instr::cconst(new val::cnil()));
	  code->placelabel(label2);
	  return;
	}else if(list.size()==4){
	  int label1=code->newlabel();
	  int label2=code->newlabel();
	  compileexpr(list[1],code);
	  code->append(new bytecode::instr::cjz(label1));
	  compileexpr(list[2],code);
	  code->append(new bytecode::instr::cjump(label2));
	  code->placelabel(label1);
	  compileexpr(list[3],code);
	  code->placelabel(label2);
	  return;
	}else{
	  error(expr)<<"'if' takes two or three arguments"<<std::endl;
	  return;
	}
      }else if(cidentmatcher("while").matches(list[0])){
	if(list.size()!=3){
	  error(expr)<<"'while' takes two arguments"<<std::endl;
	  return;
	}
	int label1=code->newlabel();
	int label2=code->newlabel();
	code->placelabel(label1);
	compileexpr(list[1],code);
	code->append(new bytecode::instr::cjz(label2));
	compileexpr(list[2],code);
	code->append(new bytecode::instr::cpop());
	code->append(new bytecode::instr::cjump(label1));
	code->placelabel(label2);
	code->append(new bytecode::instr::cconst(new val::cnil()));
	return;
      }else if(cidentmatcher("progn").matches(list[0])){
	if(list.size()==1){
	  code->append(new bytecode::instr::cconst(new val::cnil()));
	  return;
	}
	for(unsigned int i=1;i<list.size()-1;i++){
	  compileexpr(list[i],code);
	  code->append(new bytecode::instr::cpop());
	}
	compileexpr(list[list.size()-1],code);
	return;
      }else if(cidentmatcher("setq").matches(list[0])){
	if(list.size()!=3){
	  error(expr)<<"'setq' takes two arguments"<<std::endl;
	  return;
	}
	std::string ident;
	if(!canyidentmatcher(ident).matches(list[1])){
	  error(expr)<<"'setq' must be applied to identifier"<<std::endl;
	  return;
	}
	compileexpr(list[2],code);
	code->append(new bytecode::instr::cdup());
	storevar(ident,code,expr);
	return;
      }else if(cidentmatcher("let").matches(list[0])){
	if(list.size()<3){
	  error(expr)<<"'let' takes at least two arguments"<<std::endl;
	  return;
	}
	std::vector<val::cvalptr> decls;
	if(!canylistmatcher(decls).matches(list[1])){
	  error(expr)<<"'let' must be applied to a list of pairs"<<std::endl;
	  return;
	}
	enterscope(decls.size(),code);
	for(unsigned int i=0;i<decls.size();i++){
	  std::vector<val::cvalptr> decl;
	  if(!canylistmatcher(decl).matches(decls[i])){
	    error(expr)<<"'let' must be applied to a list of pairs"<<std::endl;
	    symtab.popscope();
	    return;
	  }
	  std::string name;
	  if(!canyidentmatcher(name).matches(decl[0])){
	    error(expr)<<"'let' pairs must begin with identifiers"<<std::endl;
	    return;
	  }
	  compileexpr(decl[1],code);
	  try{
	    int id=symtab.locals->declvar(name);
	    code->append(new bytecode::instr::cstorelocal(id));
	  }catch(const exception::redeclared_variable& e){
	    //shouldn't happen
	    error(expr)<<"Variable '"<<e.name<<"' redeclared"<<std::endl;
	    return;
	  }
	}
	for(unsigned int i=2;i<list.size()-1;i++){
	  compileexpr(list[i],code);
	  code->append(new bytecode::instr::cpop());
	}
	compileexpr(list[list.size()-1],code);
	exitscope(decls.size(),code);
	return;
      }else{
	std::string ident;
	if(!canyidentmatcher(ident).matches(list[0])){
	  error(expr)<<"Function calls must"
		     <<" begin with an identifier"<<std::endl;
	  return;
	}
	for(unsigned int i=1;i<list.size();i++){
	  compileexpr(list[i],code);
	}
	try{
	  int id=symtab.rsrvfunc(ident,list.size()-1);
	  code->append(new bytecode::instr::ccallfunc(id,list.size()-1));
	  return;
	}catch(const exception::mismatched_arguments& e){
	  errlog->error()<<"Function '"<<e.name<<"'"
			<<" called with "<<e.nargs2<<" parameters,"
			<<" but only takes "<<e.nargs1<<std::endl;
	  return;
	}
      }
    }
    void ccompiler::finalize(){
      if(errlog->errcnt>0){
	std::cerr<<"Compiler: "<<errlog->errcnt<<" errors"<<std::endl;
	return;
      }
      //validate all functions that are called exist
      std::map<int,std::string> invfuncs;
      for(std::map<std::string,int>::iterator
	    it=symtab.reflect->funcs.begin();
	  it!=symtab.reflect->funcs.end();it++){
	invfuncs[it->second]=it->first;
      }
      for(unsigned int i=0;i<environ->functions.size();i++){
	if(environ->functions[i].isnull()){
	  errlog->error()<<"Error: function '"<<invfuncs[i]<<"'"
			<<" does not exist"<<std::endl;
	}
      }
      environ->globalscnt=symtab.globals->idents.size();
    }
  }
}
