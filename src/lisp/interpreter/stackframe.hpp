#ifndef LISP_INTERPRETER_STACKFRAME_HPP_
#define LISP_INTERPRETER_STACKFRAME_HPP_

#include "../val/val.hpp"
#include "../bytecode/bytecode.hpp"

namespace lisp{
  namespace interpreter{
    struct cstackframe{
      std::vector<val::cvalptr> locals;
      bytecode::cbytecodeptr code;
      int curinstr;
      cstackframe(bytecode::cbytecodeptr code);
    };
  }
}

#endif//LISP_INTERPRETER_STACKFRAME_HPP_
