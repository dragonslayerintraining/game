#include "scriptbuilder.hpp"

#include "../function/basicfunc.hpp"

#include <vector>
#include <fstream>

#include "../val/matcher.hpp"
#include "../builtinfuncs/writeline.hpp"
#include "../builtinfuncs/string.hpp"
#include "../builtinfuncs/list.hpp"
#include "../builtinfuncs/types.hpp"
#include "../builtinfuncs/comp.hpp"
#include "../builtinfuncs/arith.hpp"
#include "../builtinfuncs/logic.hpp"
#include "../builtinfuncs/random.hpp"

namespace lisp{
  namespace script{
    cscriptbuilder::cscriptbuilder():
      env(new environ::cenviron()),log(new errlog::cerrlog()),
      cmplr(env,log),reflect(cmplr.symtab.reflect){
    }
    struct cscriptbuilder& cscriptbuilder::importfile(std::string path){
      std::ifstream fin(path.c_str());
      std::vector<val::cvalptr> val=lisp::reader::readall(fin);
      
      for(unsigned int i=0;i<val.size();i++){
	//struct ctostrvisitor tostr;
	//val[i]->accept(tostr);
	//std::cout<<"Value: "<<tostr.getstr()<<std::endl;
	std::vector<val::cvalptr> list;
	std::string path;
	if(val::matcher::canylistmatcher(list).matches(val[i])&&
	   (list.size()==2)&&
	   val::matcher::cidentmatcher("import").matches(list[0])&&
	   val::matcher::canystrmatcher(path).matches(list[1])){
	  importfile(path);
	}else{
	  cmplr.compileglobal(val[i]);
	}
      }
      return *this;
    }
    struct cscriptbuilder& cscriptbuilder::declbuiltin(std::string name,int nargs,
						       builtinfuncs::cbasicptr func){
      cmplr.symtab.declfunc(name,nargs,
			    new function::cbasicfunc(func));
      return *this;
    }
    struct cscriptbuilder& cscriptbuilder::enableconsoleinput(){
      return *this;
    }
    struct cscriptbuilder& cscriptbuilder::enableconsoleoutput(){
      declbuiltin("write-line",1,new builtinfuncs::cwriteline());
      return *this;
    }
    struct cscriptbuilder& cscriptbuilder::enablebasics(){
      declbuiltin("string-concat",-1,new builtinfuncs::string::cconcat());
      declbuiltin("string-equals",2,new builtinfuncs::string::cequals());
      declbuiltin("cons",2,new builtinfuncs::list::ccons());
      declbuiltin("list",-1,new builtinfuncs::list::clist());
      declbuiltin("first",1,new builtinfuncs::list::cfirst());
      declbuiltin("rest",1,new builtinfuncs::list::crest());
      declbuiltin("equals",2,new builtinfuncs::types::cequals());
      declbuiltin("to-string",1,new builtinfuncs::types::ctostring());
      declbuiltin("int",1,new builtinfuncs::types::cint());
      declbuiltin("double",1,new builtinfuncs::types::cdbl());
      declbuiltin("<",2,new builtinfuncs::comp::clt());
      declbuiltin("==",2,new builtinfuncs::comp::ceq());
      declbuiltin("<=",2,new builtinfuncs::comp::cle());
      declbuiltin(">",2,new builtinfuncs::comp::cgt());
      declbuiltin("!=",2,new builtinfuncs::comp::cne());
      declbuiltin(">=",2,new builtinfuncs::comp::cge());
      declbuiltin("+",2,new builtinfuncs::arith::cadd());
      declbuiltin("-",2,new builtinfuncs::arith::csub());
      declbuiltin("*",2,new builtinfuncs::arith::cmul());
      declbuiltin("/",2,new builtinfuncs::arith::cdiv());
      declbuiltin("%",2,new builtinfuncs::arith::cmod());
      declbuiltin("max",2,new builtinfuncs::arith::cmax());
      declbuiltin("min",2,new builtinfuncs::arith::cmin());
      declbuiltin("sqrt",2,new builtinfuncs::arith::csqrt());
      declbuiltin("pyth",2,new builtinfuncs::arith::cpyth());
      declbuiltin("and",-1,new builtinfuncs::logic::cand());
      declbuiltin("or",-1,new builtinfuncs::logic::cor());
      declbuiltin("xor",-1,new builtinfuncs::logic::cxor());
      declbuiltin("not",1,new builtinfuncs::logic::cnot());
      declbuiltin("rand-select",-1,new builtinfuncs::random::crandselect());
      declbuiltin("rand-range",2,new builtinfuncs::random::crandrange());
      return *this;
    }
    interpreter::cinterpreterptr cscriptbuilder::finalize(){
      cmplr.finalize();
      if(log->errcnt>0){
	return NULL;
      }
      return new lisp::interpreter::cinterpreter(env,reflect);
    }
  }
}
