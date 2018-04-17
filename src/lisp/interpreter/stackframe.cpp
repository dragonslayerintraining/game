#include "stackframe.hpp"

namespace lisp{
  namespace interpreter{
    cstackframe::cstackframe(bytecode::cbytecodeptr code):
      code(code),curinstr(0){
    }
  }
}
