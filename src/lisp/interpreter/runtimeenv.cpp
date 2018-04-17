#include "runtimeenv.hpp"
#include "../val/tostr.hpp"
#include "../val/matcher.hpp"

#include <iostream>
#include <cassert>

namespace lisp{
  namespace interpreter{
    struct cinterpretvisitor: public bytecode::instr::ivisitor{
      struct cruntimeenv& rte;
      cinterpretvisitor(struct cruntimeenv& rte):rte(rte){
      }
      void visit(const struct bytecode::instr::cconst& instr){
	rte.stk.push_back(instr.val);
      }
      void visit(const struct bytecode::instr::cpop& instr){
	(void)instr;
	rte.stk.pop_back();
      }
      void visit(const struct bytecode::instr::cdup& instr){
	(void)instr;
	rte.stk.push_back(rte.stk.back());
      }
      void visit(const struct bytecode::instr::creservelocal& instr){
	for(int i=0;i<instr.numvars;i++){
	  rte.frames.top().locals.push_back(new val::cnil());
	}
      }
      void visit(const struct bytecode::instr::cfreelocal& instr){
	for(int i=0;i<instr.numvars;i++){
	  rte.frames.top().locals.pop_back();
	}
      }
      void visit(const struct bytecode::instr::cloadlocal& instr){
	val::cvalptr val=rte.frames.top().locals[instr.id];
	rte.stk.push_back(val);
      }
      void visit(const struct bytecode::instr::cstorelocal& instr){
	val::cvalptr val=rte.stk.back();
	assert(!rte.stk.empty());
	rte.stk.pop_back();
	rte.frames.top().locals[instr.id]=val;
      }
      void visit(const struct bytecode::instr::cloadglobal& instr){
	val::cvalptr val=rte.globals->globals[instr.id];
	rte.stk.push_back(val);
      }
      void visit(const struct bytecode::instr::cstoreglobal& instr){
	val::cvalptr val=rte.stk.back();
	assert(!rte.stk.empty());
	rte.stk.pop_back();
	rte.globals->globals[instr.id]=val;
      }
      void visit(const struct bytecode::instr::cjump& instr){
	rte.frames.top().curinstr=instr.label-1;
      }
      void visit(const struct bytecode::instr::cjnz& instr){
	val::cvalptr val=rte.stk.back();
	rte.stk.pop_back();
	if(!val::matcher::cnilmatcher().matches(val)){
	  rte.frames.top().curinstr=instr.label-1;
	}
      }
      void visit(const struct bytecode::instr::cjz& instr){
	val::cvalptr val=rte.stk.back();
	rte.stk.pop_back();
	if(val::matcher::cnilmatcher().matches(val)){
	  rte.frames.top().curinstr=instr.label-1;
	}
      }
      void visit(const struct bytecode::instr::ccallfunc& instr){
	//std::cerr<<"instr.nargs="<<instr.nargs<<std::endl;
        rte.environ->functions[instr.id]->call(rte,instr.nargs);
      }
    };
    cruntimeenv::cruntimeenv(environ::cenvironptr environ,
			     cglobalsptr globals):
      environ(environ),globals(globals){
    }
    void cruntimeenv::step(){
      if(frames.empty()){
	return;
      }
      struct cstackframe& curframe=frames.top();
      if(curframe.curinstr>=(int)curframe.code->code.size()){
	frames.pop();
	return;
      }
      //std::cerr<<"Step: curinstr="<<curframe.curinstr<<std::endl;
      struct cinterpretvisitor visitor(*this);
      curframe.code->code[curframe.curinstr]->accept(visitor);
      curframe.curinstr++;
    }
    void cruntimeenv::run(){
      while(!frames.empty()){
	step();
      }
    }
  }
}
