#include "types.hpp"
#include "../val/tostr.hpp"
#include "../val/extract.hpp"
#include "../val/matcher.hpp"
#include "../val/equals.hpp"
#include <iostream>
#include <cassert>

namespace lisp{
  namespace builtinfuncs{
    namespace types{
      val::cvalptr ctostring::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	struct val::ctostrvisitor tostr;
	args[0]->accept(tostr);
	return new val::cstr(tostr.getstr());
      }
      val::cvalptr cequals::call(std::vector<val::cvalptr> args){
	if(args.size()!=2){
	  return new val::cnil();
	}
	if(val::equals(args[0],args[1])){
	  return new val::cident("t");
	}else{
	  return new val::cnil();
	}
      }
      val::cvalptr cint::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	struct val::extract::cnumbervisitor visitor;
	args[0]->accept(visitor);
	if(visitor.success){
	  return new val::cint(visitor.intval);
	}else{
	  return new val::cnil();
	}
      }
      val::cvalptr cdbl::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	struct val::extract::cnumbervisitor visitor;
	args[0]->accept(visitor);
	if(visitor.success){
	  return new val::cdbl(visitor.dblval);
	}else{
	  return new val::cnil();
	}
      }
    }
  }
}
