#include "matcher.hpp"
#include "extract.hpp"

namespace lisp{
  namespace val{
    namespace matcher{
      imatcher::~imatcher(){
      }
      //deep match
      bool cnilmatcher::matches(cvalptr val){
	struct extract::cnilvisitor visitor;
	val->accept(visitor);
	return visitor.success;
      }
      cpairmatcher::cpairmatcher(cmatcherptr first,cmatcherptr rest):
	first(first),rest(rest){
      }
      bool cpairmatcher::matches(cvalptr val){
	struct extract::cpairvisitor visitor;
	val->accept(visitor);
	return visitor.success&&
	  first->matches(visitor.first)&&
	  rest->matches(visitor.rest);
      }
      cintmatcher::cintmatcher(int val):val(val){
      }
      bool cintmatcher::matches(cvalptr val){
	struct extract::cintvisitor visitor;
	val->accept(visitor);
	return visitor.success&&(visitor.ret==this->val);
      }
      cdblmatcher::cdblmatcher(double val):val(val){
      }
      bool cdblmatcher::matches(cvalptr val){
	struct extract::cdblvisitor visitor;
	val->accept(visitor);
	return visitor.success&&(visitor.ret==this->val);
      }
      cstrmatcher::cstrmatcher(std::string val):val(val){
      }
      bool cstrmatcher::matches(cvalptr val){
	struct extract::cstrvisitor visitor;
	val->accept(visitor);
	return visitor.success&&(visitor.ret==this->val);
      }
      cidentmatcher::cidentmatcher(std::string val):val(val){
      }
      bool cidentmatcher::matches(cvalptr val){
	struct extract::cidentvisitor visitor;
	val->accept(visitor);
	return visitor.success&&(visitor.ret==this->val);
      }
      //shallow match
      bool canynilmatcher::matches(cvalptr val){
	struct extract::cnilvisitor visitor;
	val->accept(visitor);
	return visitor.success;
      }
      canypairmatcher::canypairmatcher(cvalptr& first,cvalptr& rest):
	first(first),rest(rest){
      }
      bool canypairmatcher::matches(cvalptr val){
	struct extract::cpairvisitor visitor;
	val->accept(visitor);
	if(visitor.success){
	  this->first=visitor.first;
	  this->rest=visitor.rest;
	}
	return visitor.success;
      }
      canyintmatcher::canyintmatcher(int& val):val(val){
      }
      bool canyintmatcher::matches(cvalptr val){
	struct extract::cintvisitor visitor;
	val->accept(visitor);
	if(visitor.success){
	  this->val=visitor.ret;
	}
	return visitor.success;
      }
      canydblmatcher::canydblmatcher(double& val):val(val){
      }
      bool canydblmatcher::matches(cvalptr val){
	struct extract::cdblvisitor visitor;
	val->accept(visitor);
	if(visitor.success){
	  this->val=visitor.ret;
	}
	return visitor.success;
      }
      canystrmatcher::canystrmatcher(std::string& val):val(val){
      }
      bool canystrmatcher::matches(cvalptr val){
	struct extract::cstrvisitor visitor;
	val->accept(visitor);
	if(visitor.success){
	  this->val=visitor.ret;
	}
	return visitor.success;
      }
      canyidentmatcher::canyidentmatcher(std::string& val):val(val){
      }
      bool canyidentmatcher::matches(cvalptr val){
	struct extract::cidentvisitor visitor;
	val->accept(visitor);
	if(visitor.success){
	  this->val=visitor.ret;
	}
	return visitor.success;
      }
      //misc
      canylistmatcher::canylistmatcher(std::vector<cvalptr>& val):val(val){
      }
      bool canylistmatcher::matches(cvalptr val){
	struct extract::clistvisitor visitor;
	val->accept(visitor);
	if(visitor.success){
	  this->val=visitor.list;
	}
	return visitor.success;
      }
      cboolmatcher::cboolmatcher(bool val):val(val){
      }
      bool cboolmatcher::matches(cvalptr val){
	struct extract::cboolvisitor visitor;
	val->accept(visitor);
	return (this->val==visitor.ret);
      }
      canyboolmatcher::canyboolmatcher(bool& val):val(val){
      }
      bool canyboolmatcher::matches(cvalptr val){
	struct extract::cboolvisitor visitor;
	val->accept(visitor);
	this->val=visitor.ret;
	return true;
      }
      canymatcher::canymatcher(cvalptr& val):val(val){
      }
      bool canymatcher::matches(cvalptr val){
	this->val=val;
	return true;
      }
      cstorematcher::cstorematcher(cmatcherptr m,cvalptr& val):
	m(m),val(val){
      }
      bool cstorematcher::matches(cvalptr val){
	this->val=val;
	return m->matches(val);
      }
      cormatcher::cormatcher(cmatcherptr m1,cmatcherptr m2,int& index):
	m1(m1),m2(m2),index(index){
      }
      bool cormatcher::matches(cvalptr val){
	if(m1->matches(val)){
	  index=0;
	  return true;
	}
	if(m2->matches(val)){
	  index=1;
	  return true;
	}
	return false;
      }
    }
  }
}
