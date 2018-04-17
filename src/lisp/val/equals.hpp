#ifndef LISP_VAL_EQUALS_HPP_
#define LISP_VAL_EQUALS_HPP_

#include "matcher.hpp"

namespace lisp{
  namespace val{
    matcher::cmatcherptr equalsmatcher(val::cvalptr val);
    bool equals(val::cvalptr val1,val::cvalptr val2);
  }
}

#endif//LISP_VAL_EQUALS_HPP_
