#include "summarize.hpp"
#include "matcher.hpp"

namespace lisp{
  namespace val{
    csummarizevisitor::csummarizevisitor(unsigned int maxdepth):
      maxdepth(maxdepth),depth(1){
    }
    void csummarizevisitor::visit(const struct cnil& var){
      (void)var;
      stream<<"nil";
    }
    void csummarizevisitor::visit(const struct cpair& var){
      if(depth>maxdepth){
	stream<<"(...)";
	return;
      }

      stream<<"(";
      var.first->accept(*this);

      std::vector<cvalptr> list;
      if(matcher::canylistmatcher(list).matches(var.rest)){
	for(unsigned int i=0;i<list.size();i++){
	  if(i>=maxdepth){
	    stream<<"...";
	    break;
	  }
	  stream<<" ";
	  ++depth;
	  list[i]->accept(*this);
	  --depth;
	}
      }else{
	stream<<" . ";
	++depth;
	var.rest->accept(*this);
	--depth;
      }
      stream<<")";
    }
    void csummarizevisitor::visit(const struct cint& var){
      stream<<var.val;
    }
    void csummarizevisitor::visit(const struct cdbl& var){
      stream<<var.val;
    }
    void csummarizevisitor::visit(const struct cstr& var){
      stream<<'"'<<var.val<<'"';
    }
    void csummarizevisitor::visit(const struct cident& var){
      stream<<var.val;
    }
    std::string csummarizevisitor::getstr(){
      return stream.str();
    }
  }
}
