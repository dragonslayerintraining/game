#ifndef LISP_VAL_TOSTR_HPP_
#define LISP_VAL_TOSTR_HPP_

#include "val.hpp"
#include <sstream>

namespace lisp{
  namespace val{
    struct ctostrvisitor: public ivisitor{
      std::stringstream stream;
      void visit(const struct cnil& var);
      void visit(const struct cpair& var);
      void visit(const struct cint& var);
      void visit(const struct cdbl& var);
      void visit(const struct cstr& var);
      void visit(const struct cident& var);
      std::string getstr();
    };
  }
}

#endif//LISP_VAL_TOSTR_HPP_
