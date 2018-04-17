#include "random.hpp"
#include "../val/tostr.hpp"
#include "../val/extract.hpp"
#include "../val/matcher.hpp"
#include <iostream>
#include <cassert>
#include <cstdlib>

namespace lisp{
  namespace builtinfuncs{
    namespace random{
      val::cvalptr crandselect::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	std::vector<val::cvalptr> list;
	if(val::matcher::canylistmatcher(list).matches(args[0])){
	  if(list.size()>0){
	    return list[rand()%list.size()];
	  }else{
	    return new val::cnil();
	  }
	}
	return new val::cnil();
      }
      val::cvalptr crandrange::call(std::vector<val::cvalptr> args){
	if(args.size()!=2){
	  return new val::cnil();
	}
	int min,max;
	if(val::matcher::canyintmatcher(min).matches(args[0])&&
	   val::matcher::canyintmatcher(max).matches(args[0])){
	  if(max>min){
	    return new val::cint(rand()%(max-min)+min);
	  }else{
	    return new val::cnil();
	  }
	}
	return new val::cnil();
      }
    }
  }
}
