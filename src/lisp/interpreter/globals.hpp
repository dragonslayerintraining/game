#ifndef LISP_INTERPRETER_GLOBALS_HPP_
#define LISP_INTERPRETER_GLOBALS_HPP_

#include "../val/val.hpp"
#include "../../util/refcntptrmod.hpp"
#include <vector>

namespace lisp{
  namespace interpreter{
    struct cglobals{
      std::vector<val::cvalptr> globals;
      cglobals(unsigned int size);
    };
    typedef util::crefcntptrmod<struct cglobals> cglobalsptr;
  }
}

#endif//LISP_INTERPRETER_GLOBALS_HPP_
