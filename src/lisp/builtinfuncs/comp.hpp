#ifndef LISP_BUILTINFUNCS_COMP_HPP_
#define LISP_BUILTINFUNCS_COMP_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    namespace comp{
      struct clt: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct ceq: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cle: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cgt: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cne: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cge: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
    }
  }
}

#endif//LISP_BUILTINFUNCS_COMP_HPP_
