#ifndef LISP_BUILTINFUNCS_STRING_HPP_
#define LISP_BUILTINFUNCS_STRING_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    namespace string{
      struct cconcat: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cequals: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
    }
  }
}

#endif//LISP_BUILTINFUNCS_STRING_HPP_
