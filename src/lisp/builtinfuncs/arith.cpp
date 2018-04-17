#include "arith.hpp"
#include "../val/tostr.hpp"
#include "../val/extract.hpp"
#include "../val/matcher.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>

namespace lisp{
  namespace builtinfuncs{
    namespace arith{
      static val::cvalptr binaryop(struct ibinop& op,
				   const std::vector<val::cvalptr>& args){
	if(args.size()!=2){
	  return new val::cnil();
	}
	struct val::extract::cnumbervisitor num1,num2;
	args[0]->accept(num1);
	args[1]->accept(num2);
	if(num1.success&&num2.success){
	  if(num1.isint&&num2.isint){
	    return new val::cint(op(num1.intval,num2.intval));
	  }else{
	    return new val::cdbl(op(num1.dblval,num2.dblval));
	  }
	}
	return new val::cnil();
      }
      int cadd::operator()(int n1,int n2){
	return n1+n2;
      }
      double cadd::operator()(double n1,double n2){
	return n1+n2;
      }
      val::cvalptr cadd::call(std::vector<val::cvalptr> args){
	return binaryop(*this,args);
      }
      int csub::operator()(int n1,int n2){
	return n1-n2;
      }
      double csub::operator()(double n1,double n2){
	return n1-n2;
      }
      val::cvalptr csub::call(std::vector<val::cvalptr> args){
	return binaryop(*this,args);
      }
      int cmul::operator()(int n1,int n2){
	return n1*n2;
      }
      double cmul::operator()(double n1,double n2){
	return n1*n2;
      }
      val::cvalptr cmul::call(std::vector<val::cvalptr> args){
	return binaryop(*this,args);
      }
      int cdiv::operator()(int n1,int n2){
	if(n2==0){return 0;}
	return n1/n2;
      }
      double cdiv::operator()(double n1,double n2){
	if(n2==0){return 0;}
	return n1/n2;
      }
      val::cvalptr cdiv::call(std::vector<val::cvalptr> args){
	return binaryop(*this,args);
      }
      int cmod::operator()(int n1,int n2){
	if(n2==0){return 0;}
	return n1%n2;
      }
      double cmod::operator()(double n1,double n2){
	if(n2==0){return 0;}
	return n1-int(n1/n2)*n2;
      }
      val::cvalptr cmod::call(std::vector<val::cvalptr> args){
	return binaryop(*this,args);
      }
      int cmax::operator()(int n1,int n2){
	return std::max(n1,n2);
      }
      double cmax::operator()(double n1,double n2){
	return std::max(n1,n2);
      }
      val::cvalptr cmax::call(std::vector<val::cvalptr> args){
	return binaryop(*this,args);
      }
      int cmin::operator()(int n1,int n2){
	return std::min(n1,n2);
      }
      double cmin::operator()(double n1,double n2){
	return std::min(n1,n2);
      }
      val::cvalptr cmin::call(std::vector<val::cvalptr> args){
	return binaryop(*this,args);
      }
      val::cvalptr csqrt::call(std::vector<val::cvalptr> args){
	if(args.size()!=1){
	  return new val::cnil();
	}
	double val;
	if(val::matcher::canydblmatcher(val).matches(args[0])){
	  return new val::cdbl(std::sqrt(val));
	}
	return new val::cnil();
      }
      val::cvalptr cpyth::call(std::vector<val::cvalptr> args){
	double magn2=0;
	for(unsigned int i=0;i<args.size();i++){
	  double val;
	  if(val::matcher::canydblmatcher(val).matches(args[i])){
	    magn2+=val*val;
	  }else{
	    return new val::cnil();
	  }
	}
	return new val::cdbl(std::sqrt(magn2));
      }
    }
  }
}
