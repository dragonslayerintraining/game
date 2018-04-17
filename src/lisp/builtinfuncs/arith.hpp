#ifndef LISP_BUILTINFUNCS_ARITH_HPP_
#define LISP_BUILTINFUNCS_ARITH_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    namespace arith{
      struct ibinop: public ibasic{
	virtual int operator()(int n1,int n2)=0;
	virtual double operator()(double n1,double n2)=0;
      };
      struct cadd: public ibinop{
	int operator()(int n1,int n2);
	double operator()(double n1,double n2);
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct csub: public ibinop{
	int operator()(int n1,int n2);
	double operator()(double n1,double n2);
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cmul: public ibinop{
	int operator()(int n1,int n2);
	double operator()(double n1,double n2);
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cdiv: public ibinop{
	int operator()(int n1,int n2);
	double operator()(double n1,double n2);
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cmod: public ibinop{
	int operator()(int n1,int n2);
	double operator()(double n1,double n2);
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cmax: public ibinop{
	int operator()(int n1,int n2);
	double operator()(double n1,double n2);
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cmin: public ibinop{
	int operator()(int n1,int n2);
	double operator()(double n1,double n2);
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct csqrt: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cpyth: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
    }
  }
}

#endif//LISP_BUILTINFUNCS_ARITH_HPP_
