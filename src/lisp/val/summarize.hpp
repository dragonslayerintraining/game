#ifndef LISP_VAL_SUMMARIZE_HPP_
#define LISP_VAL_SUMMARIZE_HPP_

#include "val.hpp"
#include <sstream>

namespace lisp{
  namespace val{
    struct csummarizevisitor: public ivisitor{
      std::stringstream stream;
      unsigned int maxdepth;
      unsigned int depth;
      csummarizevisitor(unsigned int maxdepth=2);
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

#endif//LISP_VAL_SUMMARIZE_HPP_
