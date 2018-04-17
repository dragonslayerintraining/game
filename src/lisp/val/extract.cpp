#include "extract.hpp"

namespace lisp{
  namespace val{
    namespace extract{
      void cnilvisitor::visit(const struct cnil& var){
	(void)var;
	success=true;
      }
      void cnilvisitor::visit(const struct cpair& var){(void)var;success=false;}
      void cnilvisitor::visit(const struct cint& var){(void)var;success=false;}
      void cnilvisitor::visit(const struct cdbl& var){(void)var;success=false;}
      void cnilvisitor::visit(const struct cstr& var){(void)var;success=false;}
      void cnilvisitor::visit(const struct cident& var){(void)var;success=false;}

      void cpairvisitor::visit(const struct cnil& var){(void)var;success=false;}
      void cpairvisitor::visit(const struct cpair& var){
	success=true;
	first=var.first;
	rest=var.rest;
      }
      void cpairvisitor::visit(const struct cint& var){(void)var;success=false;}
      void cpairvisitor::visit(const struct cdbl& var){(void)var;success=false;}
      void cpairvisitor::visit(const struct cstr& var){(void)var;success=false;}
      void cpairvisitor::visit(const struct cident& var){(void)var;success=false;}

      void cintvisitor::visit(const struct cnil& var){(void)var;success=false;}
      void cintvisitor::visit(const struct cpair& var){(void)var;success=false;}
      void cintvisitor::visit(const struct cint& var){
	success=true;
	ret=var.val;
      }
      void cintvisitor::visit(const struct cdbl& var){(void)var;success=false;}
      void cintvisitor::visit(const struct cstr& var){(void)var;success=false;}
      void cintvisitor::visit(const struct cident& var){(void)var;success=false;}

      void cdblvisitor::visit(const struct cnil& var){(void)var;success=false;}
      void cdblvisitor::visit(const struct cpair& var){(void)var;success=false;}
      void cdblvisitor::visit(const struct cint& var){(void)var;success=false;}
      void cdblvisitor::visit(const struct cdbl& var){
	success=true;
	ret=var.val;
      }
      void cdblvisitor::visit(const struct cstr& var){(void)var;success=false;}
      void cdblvisitor::visit(const struct cident& var){(void)var;success=false;}

      void cstrvisitor::visit(const struct cnil& var){(void)var;success=false;}
      void cstrvisitor::visit(const struct cpair& var){(void)var;success=false;}
      void cstrvisitor::visit(const struct cint& var){(void)var;success=false;}
      void cstrvisitor::visit(const struct cdbl& var){(void)var;success=false;}
      void cstrvisitor::visit(const struct cstr& var){
	success=true;
	ret=var.val;
      }
      void cstrvisitor::visit(const struct cident& var){(void)var;success=false;}

      void cidentvisitor::visit(const struct cnil& var){(void)var;success=false;}
      void cidentvisitor::visit(const struct cpair& var){(void)var;success=false;}
      void cidentvisitor::visit(const struct cint& var){(void)var;success=false;}
      void cidentvisitor::visit(const struct cdbl& var){(void)var;success=false;}
      void cidentvisitor::visit(const struct cstr& var){(void)var;success=false;}
      void cidentvisitor::visit(const struct cident& var){
	success=true;
	ret=var.val;
      }
      
      void cboolvisitor::visit(const struct cnil& var){(void)var;ret=false;}
      void cboolvisitor::visit(const struct cpair& var){(void)var;ret=true;}
      void cboolvisitor::visit(const struct cint& var){(void)var;ret=true;}
      void cboolvisitor::visit(const struct cdbl& var){(void)var;ret=true;}
      void cboolvisitor::visit(const struct cstr& var){(void)var;ret=true;}
      void cboolvisitor::visit(const struct cident& var){(void)var;ret=true;}

      void cnumbervisitor::visit(const struct cnil& var){(void)var;success=false;}
      void cnumbervisitor::visit(const struct cpair& var){(void)var;success=false;}
      void cnumbervisitor::visit(const struct cint& var){
	success=true;
	isint=true;
	isdbl=false;
	intval=var.val;
	dblval=var.val;
      }
      void cnumbervisitor::visit(const struct cdbl& var){
	success=true;
	isint=false;
	isdbl=true;
	intval=var.val;
	dblval=var.val;
      }
      void cnumbervisitor::visit(const struct cstr& var){(void)var;success=false;}
      void cnumbervisitor::visit(const struct cident& var){(void)var;success=false;}
      void clistvisitor::visit(const struct cnil& var){(void)var;success=true;}
      void clistvisitor::visit(const struct cpair& var){
	list.push_back(var.first);
	var.rest->accept(*this);
	//does not modify success
      }
      void clistvisitor::visit(const struct cint& var){(void)var;success=false;}
      void clistvisitor::visit(const struct cdbl& var){(void)var;success=false;}
      void clistvisitor::visit(const struct cstr& var){(void)var;success=false;}
      void clistvisitor::visit(const struct cident& var){(void)var;success=false;}
    }
  }
}
