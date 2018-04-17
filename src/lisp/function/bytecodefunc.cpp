#include "bytecodefunc.hpp"

namespace lisp{
  namespace function{
    cbytecodefunc::cbytecodefunc(bytecode::cbytecodeptr code):code(code){
    }
    void cbytecodefunc::call(struct interpreter::cruntimeenv& rte,
			     unsigned int nargs){
      (void)nargs;
      rte.frames.push(interpreter::cstackframe(code));
    }
  }
}
