#ifndef LISP_VAL_HPP_
#define LISP_VAL_HPP_

#include "../../util/refcntptrconst.hpp"
#include <string>

namespace lisp{
  namespace val{
    struct ivisitor;
    struct ival{
      virtual void accept(struct ivisitor& visitor)const=0;
      virtual ~ival();
    };
    typedef util::crefcntptrconst<struct ival> cvalptr;
    struct cnil: public ival{
      void accept(struct ivisitor& visitor)const;
    };
    struct cpair: public ival{
      cvalptr first,rest;
      cpair(cvalptr first,cvalptr rest);
      void accept(struct ivisitor& visitor)const;
    };
    struct cint: public ival{
      int val;
      cint(int val);
      void accept(struct ivisitor& visitor)const;
    };
    struct cdbl: public ival{
      double val;
      cdbl(double val);
      void accept(struct ivisitor& visitor)const;
    };
    struct cstr: public ival{
      std::string val;
      cstr(std::string val);
      void accept(struct ivisitor& visitor)const;
    };
    struct cident: public ival{
      std::string val;
      cident(std::string val);
      void accept(struct ivisitor& visitor)const;
    };
    struct ivisitor{
      virtual void visit(const struct cnil& var)=0;
      virtual void visit(const struct cpair& var)=0;
      virtual void visit(const struct cint& var)=0;
      virtual void visit(const struct cdbl& var)=0;
      virtual void visit(const struct cstr& var)=0;
      virtual void visit(const struct cident& var)=0;
      virtual ~ivisitor();
    };
  }
}

#endif//LISP_VAL_HPP_
