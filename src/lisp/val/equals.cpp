#include "equals.hpp"

namespace lisp{
  namespace val{
    struct cequalsmatchervisitor: public ivisitor{
      matcher::cmatcherptr ret;
      void visit(const struct cnil& var){
	(void)var;
	ret=new matcher::cnilmatcher();
      }
      void visit(const struct cpair& var){
	matcher::cmatcherptr first,rest;
	var.first->accept(*this);
	first=ret;
	var.rest->accept(*this);
	rest=ret;
	ret=new matcher::cpairmatcher(first,rest);
      }
      void visit(const struct cint& var){
	ret=new matcher::cintmatcher(var.val);
      }
      void visit(const struct cdbl& var){
	ret=new matcher::cdblmatcher(var.val);
      }
      void visit(const struct cstr& var){
	ret=new matcher::cstrmatcher(var.val);
      }
      void visit(const struct cident& var){
	ret=new matcher::cidentmatcher(var.val);
      }
    };
    matcher::cmatcherptr equalsmatcher(val::cvalptr val){
      struct cequalsmatchervisitor visitor;
      val->accept(visitor);
      return visitor.ret;
    }
    bool equals(val::cvalptr val1,val::cvalptr val2){
      return equalsmatcher(val1)->matches(val2);
    }
  }
}
