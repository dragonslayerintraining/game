#ifndef LISP_COMPILER_FINALIZELABELS_HPP_
#define LISP_COMPILER_FINALIZELABELS_HPP_

#include "../bytecode/bytecode.hpp"

namespace lisp{
  namespace compiler{
    bytecode::cbytecodeptr finalizelabels(bytecode::cbytecodeptr code);
  }
}

#endif//LISP_COMPILER_FINALIZELABELS_HPP_

