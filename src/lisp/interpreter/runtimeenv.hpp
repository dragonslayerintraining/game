#ifndef LISP_INTERPRETER_RUNTIMEENV_HPP_
#define LISP_INTERPRETER_RUNTIMEENV_HPP_

#include "../environ/environ.hpp"
#include "../val/val.hpp"
#include "stackframe.hpp"
#include "globals.hpp"
#include <stack>
#include <vector>

namespace lisp{
  namespace interpreter{
    struct cruntimeenv{
      environ::cenvironptr environ;
      std::stack<struct cstackframe> frames;
      std::vector<val::cvalptr> stk;
      cglobalsptr globals;
      cruntimeenv(environ::cenvironptr environ,cglobalsptr globals);
      void step();
      void run();
    };
  }
}

#endif//LISP_INTERPRETER_RUNTIMEENV_HPP_
