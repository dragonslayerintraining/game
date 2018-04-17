#ifndef LISP_FUNCTION_BYTECODEFUNC_HPP_
#define LISP_FUNCTION_BYTECODEFUNC_HPP_

#include "function.hpp"
#include "../bytecode/bytecode.hpp"
#include "../interpreter/runtimeenv.hpp"

namespace lisp{
  namespace function{
    struct cbytecodefunc: public ifunction{
      bytecode::cbytecodeptr code;
      cbytecodefunc(bytecode::cbytecodeptr code);
      void call(struct interpreter::cruntimeenv& rte,unsigned int nargs);
    };
  }
}

#endif//LISP_FUNCTION_BYTECODEFUNC_HPP_
