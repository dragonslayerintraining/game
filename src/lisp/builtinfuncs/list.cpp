#include "list.hpp"
#include "../val/tostr.hpp"
#include "../val/matcher.hpp"
#include "../val/equals.hpp"
#include <iostream>
#include <cassert>

namespace lisp{
  namespace builtinfuncs{
    namespace list{
      val::cvalptr ccons::call(std::vector<val::cvalptr> args){
	if(args.size()!=2){
	  return new val::cnil();
	}
	return new val::cpair(args[0],args[1]);
      }
      val::cvalptr clist::call(std::vector<val::cvalptr> args){
	val::cvalptr list=new val::cnil();
	for(int i=args.size()-1;i>=0;i--){
	  list=new val::cpair(args[i],list);
	}
	return list;
      }
      val::cvalptr cfirst::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	val::cvalptr first,rest;
	if(val::matcher::canypairmatcher(first,rest).matches(args[0])){
	  return first;
	}else{
	  return new val::cnil();
	}
      }
      val::cvalptr crest::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	val::cvalptr first,rest;
	if(val::matcher::canypairmatcher(first,rest).matches(args[0])){
	  return rest;
	}else{
	  return new val::cnil();
	}
      }
    }
  }
}
