#ifndef LISP_BUILTINFUNCS_TYPES_HPP_
#define LISP_BUILTINFUNCS_TYPES_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    namespace types{
      struct ctostring: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cequals: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cint: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cdbl: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
    }
  }
}

#endif//LISP_BUILTINFUNCS_TYPES_HPP_
