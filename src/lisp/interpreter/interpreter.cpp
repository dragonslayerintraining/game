#include "interpreter.hpp"
#include "runtimeenv.hpp"
#include "../bytecode/bytecode.hpp"
#include "../val/tostr.hpp"
#include "exception.hpp"
#include "../compiler/exception.hpp"

#include <cassert>
#include <iostream>

namespace lisp{
  namespace interpreter{
    cinterpreter::cinterpreter(environ::cenvironptr environ,
			       environ::creflectionptr reflect):
      environ(environ),reflect(reflect),
      globals(new cglobals(environ->globalscnt)){
    }
    cinterpreter::cinterpreter(environ::cenvironptr environ):
      environ(environ),reflect(NULL){
    }
    val::cvalptr cinterpreter::callfunc(int id,
					std::vector<val::cvalptr> params){
      struct cruntimeenv rte(environ,globals);
      for(unsigned int i=0;i<params.size();i++){
	rte.stk.push_back(params[i]);
      }
      environ->functions[id]->call(rte,params.size());
      rte.run();
      assert(rte.stk.size()==1);
      //struct val::ctostrvisitor tostr;
      //rte.stk.back()->accept(tostr);
      //std::cerr<<"Return: "<<tostr.getstr()<<std::endl;
      return rte.stk.back();
    }
    val::cvalptr cinterpreter::callfunc(std::string name,
					std::vector<val::cvalptr> params){
      if(reflect.isnull()){
	throw exception::reflection_disabled();
      }
      if(!reflect->funcs.count(name)){
	throw compiler::exception::undeclared_function(name);
      }
      int id=reflect->funcs[name];
      int nargs=reflect->funcnargs[name];
      if((nargs!=-1)&&
	 (nargs!=(int)params.size())){
	throw compiler::exception::mismatched_arguments(name,nargs,
							params.size());
      }
      return callfunc(id,params);
    }
  }
}
