#include "comp.hpp"
#include "../val/tostr.hpp"
#include "../val/extract.hpp"
#include "../val/matcher.hpp"
#include <iostream>
#include <cassert>

namespace lisp{
  namespace builtinfuncs{
    namespace comp{
      enum ecomp{
	COMP_IC=0,//incomparable
	COMP_LT=1,
	COMP_EQ=2,
	COMP_LE=3,
	COMP_GT=4,
	COMP_NE=5,
	COMP_GE=6
      };
      static bool _compare(val::cvalptr val1,val::cvalptr val2,
			  enum ecomp type){
	struct val::extract::cnumbervisitor num1,num2;
	val1->accept(num1);
	val2->accept(num2);
	if(num1.isint&&num2.isint){
	  int n1=num1.intval,n2=num2.intval;
	  if((n1<n2)&&(type&COMP_LT)){
	    return true;
	  }else if((n1==n2)&&(type&COMP_EQ)){
	    return true;
	  }else if((n1>n2)&&(type&COMP_GT)){
	    return true;
	  }
	}else{
	  double n1=num1.dblval,n2=num2.dblval;
	  if((n1<n2)&&(type&COMP_LT)){
	    return true;
	  }else if((n1==n2)&&(type&COMP_EQ)){
	    return true;
	  }else if((n1>n2)&&(type&COMP_GT)){
	    return true;
	  }
	}
	return false;
      }
      val::cvalptr compare(const std::vector<val::cvalptr>& args,
			   enum ecomp type){
	if(args.size()!=2){
	  return new val::cnil();
	}
	if(_compare(args[0],args[1],type)){
	  return new val::cident("t");
	}else{
	  return new val::cnil();
	}
      }
      val::cvalptr clt::call(std::vector<val::cvalptr> args){
	return compare(args,COMP_LT);
      }
      val::cvalptr ceq::call(std::vector<val::cvalptr> args){
	return compare(args,COMP_EQ);
      }
      val::cvalptr cle::call(std::vector<val::cvalptr> args){
	return compare(args,COMP_LE);
      }
      val::cvalptr cgt::call(std::vector<val::cvalptr> args){
	return compare(args,COMP_GT);
      }
      val::cvalptr cne::call(std::vector<val::cvalptr> args){
	return compare(args,COMP_NE);
      }
      val::cvalptr cge::call(std::vector<val::cvalptr> args){
	return compare(args,COMP_GE);
      }
    }
  }
}
