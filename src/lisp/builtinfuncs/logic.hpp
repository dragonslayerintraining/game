#ifndef LISP_BUILTINFUNCS_LOGIC_HPP_
#define LISP_BUILTINFUNCS_LOGIC_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    namespace logic{
      struct cand: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cor: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cxor: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cnot: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
    }
  }
}

#endif//LISP_BUILTINFUNCS_LOGIC_HPP_
