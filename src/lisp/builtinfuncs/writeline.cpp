#include "writeline.hpp"
#include "../val/tostr.hpp"
#include "../val/matcher.hpp"
#include <iostream>

namespace lisp{
  namespace builtinfuncs{
    val::cvalptr cwriteline::call(std::vector<val::cvalptr> args){
      std::string str;
      if(args.size()!=1){
	return new val::cnil();
      }
      if(val::matcher::canystrmatcher(str).matches(args[0])){
	std::cout<<str<<std::endl;
	return args[0];
      }
      return new val::cnil();
    }
  }
}
