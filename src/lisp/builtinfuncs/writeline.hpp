#ifndef LISP_BUILTINFUNCS_WRITELINE_HPP_
#define LISP_BUILTINFUNCS_WRITELINE_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    struct cwriteline: public ibasic{
      val::cvalptr call(std::vector<val::cvalptr> args);
    };
  }
}

#endif//LISP_BUILTINFUNCS_WRITELINE_HPP_
