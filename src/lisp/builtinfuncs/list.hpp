#ifndef LISP_BUILTINFUNCS_LIST_HPP_
#define LISP_BUILTINFUNCS_LIST_HPP_

#include "basic.hpp"

namespace lisp{
  namespace builtinfuncs{
    namespace list{
      struct ccons: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct clist: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct cfirst: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
      struct crest: public ibasic{
	val::cvalptr call(std::vector<val::cvalptr> args);
      };
    }
  }
}

#endif//LISP_BUILTINFUNCS_LIST_HPP_
