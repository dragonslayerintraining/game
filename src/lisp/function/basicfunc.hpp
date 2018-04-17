#ifndef LISP_FUNCTION_BASICFUNC_HPP_
#define LISP_FUNCTION_BASICFUNC_HPP_

#include "function.hpp"
#include "../builtinfuncs/basic.hpp"
#include "../interpreter/runtimeenv.hpp"

namespace lisp{
  namespace function{
    struct cbasicfunc: public ifunction{
      builtinfuncs::cbasicptr func;
      cbasicfunc(builtinfuncs::cbasicptr func);
      void call(struct interpreter::cruntimeenv& rte,
		unsigned int nargs);
    };
  }
}

#endif//LISP_FUNCTION_BASICFUNC_HPP_
