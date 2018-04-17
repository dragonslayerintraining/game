#include "val.hpp"
#include "extract.hpp"

namespace lisp{
  namespace val{
    ival::~ival(){
    }

    void cnil::accept(struct ivisitor& visitor)const{
      visitor.visit(*this);
    }
    cpair::cpair(cvalptr first,cvalptr rest):first(first),rest(rest){
    }
    void cpair::accept(struct ivisitor& visitor)const{
      visitor.visit(*this);
    }
    cint::cint(int val):val(val){
    }
    void cint::accept(struct ivisitor& visitor)const{
      visitor.visit(*this);
    }
    cdbl::cdbl(double val):val(val){
    }
    void cdbl::accept(struct ivisitor& visitor)const{
      visitor.visit(*this);
    }
    cstr::cstr(std::string val):val(val){
    }
    void cstr::accept(struct ivisitor& visitor)const{
      visitor.visit(*this);
    }
    cident::cident(std::string val):val(val){
    }
    void cident::accept(struct ivisitor& visitor)const{
      visitor.visit(*this);
    }

    ivisitor::~ivisitor(){
    }
  }
}
