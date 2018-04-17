#include "logic.hpp"
#include "../val/tostr.hpp"
#include "../val/extract.hpp"
#include "../val/matcher.hpp"
#include <iostream>
#include <cassert>

namespace lisp{
  namespace builtinfuncs{
    namespace logic{
      val::cvalptr cand::call(std::vector<val::cvalptr> args){
	for(unsigned int i=0;i<args.size();i++){
	  if(val::matcher::cboolmatcher(false).matches(args[i])){
	    return new val::cnil();
	  }
	}
	return new val::cident("t");
      }
      val::cvalptr cor::call(std::vector<val::cvalptr> args){
	for(unsigned int i=0;i<args.size();i++){
	  if(val::matcher::cboolmatcher(true).matches(args[i])){
	    return new val::cident("t");
	  }
	}
	return new val::cnil();
      }
      val::cvalptr cxor::call(std::vector<val::cvalptr> args){
	bool ret=false;
	for(unsigned int i=0;i<args.size();i++){
	  if(val::matcher::cboolmatcher(true).matches(args[i])){
	    ret=!ret;
	  }
	}
	if(ret){
	  return new val::cident("t");
	}else{
	  return new val::cnil();
	}
      }
      val::cvalptr cnot::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	if(val::matcher::cboolmatcher(true).matches(args[0])){
	  return new val::cnil();
	}
	return new val::cident("t");
      }
    }
  }
}
