#ifndef LISP_BUILTINFUNCS_RANDOM_HPP_
#define LISP_BUILTINFUNCS_RANDOM_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    namespace random{
      struct crandselect: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct crandrange: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
    }
  }
}

#endif//LISP_BUILTINFUNCS_RANDOM_HPP_
