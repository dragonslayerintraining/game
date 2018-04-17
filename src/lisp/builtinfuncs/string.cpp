#include "string.hpp"
#include "../val/tostr.hpp"
#include "../val/matcher.hpp"
#include <iostream>
#include <cassert>

namespace lisp{
  namespace builtinfuncs{
    namespace string{
      val::cvalptr cconcat::call(std::vector<val::cvalptr> args){
	std::string ret;
	for(unsigned int i=0;i<args.size();i++){
	  std::string str;
	  if(val::matcher::canystrmatcher(str).matches(args[i])){
	    ret+=str;
	  }else{
	    return new val::cnil();
	  }
	}
	return new val::cstr(ret);
      }
      val::cvalptr cequals::call(std::vector<val::cvalptr> args){
	if(args.size()!=2){
	  return new val::cnil();
	}
	std::string str1,str2;
	if(val::matcher::canystrmatcher(str1).matches(args[0])&&
	   val::matcher::canystrmatcher(str2).matches(args[1])){
	  if(str1==str2){
	    return new val::cident("t");
	  }else{
	    return new val::cnil();
	  }
	}
	return new val::cnil();
      }
    }
  }
}
