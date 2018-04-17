#ifndef LISP_BUILTINFUNCS_BASIC_HPP_
#define LISP_BUILTINFUNCS_BASIC_HPP_

#include "../val/val.hpp"
#include <vector>
#include "../../util/refcntptrmod.hpp"

namespace lisp{
  namespace builtinfuncs{
    struct ibasic{
      virtual val::cvalptr call(std::vector<val::cvalptr> args)=0;
      virtual ~ibasic();
    };
    typedef util::crefcntptrmod<struct ibasic> cbasicptr;
  }
}

#endif//LISP_BUILTINFUNCS_BASIC_HPP_
