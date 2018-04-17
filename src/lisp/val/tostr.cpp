#include "tostr.hpp"
#include "matcher.hpp"

namespace lisp{
  namespace val{
    void ctostrvisitor::visit(const struct cnil& var){
      (void)var;
      stream<<"nil";
    }
    void ctostrvisitor::visit(const struct cpair& var){
      stream<<"(";
      var.first->accept(*this);

      std::vector<cvalptr> list;
      if(matcher::canylistmatcher(list).matches(var.rest)){
	for(unsigned int i=0;i<list.size();i++){
	  stream<<" ";
	  list[i]->accept(*this);
	}
      }else{
	stream<<" . ";
	var.rest->accept(*this);
      }
      stream<<")";
    }
    void ctostrvisitor::visit(const struct cint& var){
      stream<<var.val;
    }
    void ctostrvisitor::visit(const struct cdbl& var){
      stream<<var.val;
    }
    void ctostrvisitor::visit(const struct cstr& var){
      stream<<'"'<<var.val<<'"';
    }
    void ctostrvisitor::visit(const struct cident& var){
      stream<<var.val;
    }
    std::string ctostrvisitor::getstr(){
      return stream.str();
    }
  }
}
