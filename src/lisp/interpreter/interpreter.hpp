#ifndef LISP_INTERPRETER_INTERPRETER_HPP_
#define LISP_INTERPRETER_INTERPRETER_HPP_

#include "../../util/refcntptrmod.hpp"
#include "../environ/environ.hpp"
#include "../environ/reflection.hpp"
#include "../val/val.hpp"
#include "runtimeenv.hpp"

namespace lisp{
  namespace interpreter{
    struct cinterpreter{
      environ::cenvironptr environ;
      environ::creflectionptr reflect;
      cglobalsptr globals;
      cinterpreter(environ::cenvironptr environ,
		   environ::creflectionptr reflect);
      cinterpreter(environ::cenvironptr environ);
      val::cvalptr callfunc(int id,std::vector<val::cvalptr> args);
      val::cvalptr callfunc(std::string name,std::vector<val::cvalptr> args);
    };
    typedef util::crefcntptrmod<struct cinterpreter> cinterpreterptr;
  }
}

#endif//LISP_INTERPRETER_INTERPRETER_HPP_
