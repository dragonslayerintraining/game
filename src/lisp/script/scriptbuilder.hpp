#ifndef LISP_SCRIPT_SCRIPTBUILDER_HPP_
#define LISP_SCRIPT_SCRIPTBUILDER_HPP_

#include "../val/val.hpp"
#include "../environ/environ.hpp"
#include "../environ/reflection.hpp"
#include "../errlog/errlog.hpp"
#include "../compiler/compiler.hpp"
#include "../reader/reader.hpp"
#include "../interpreter/interpreter.hpp"
#include "../builtinfuncs/basic.hpp"

namespace lisp{
  namespace script{
    struct cscriptbuilder{
      environ::cenvironptr env;
      errlog::cerrlogptr log;
      struct compiler::ccompiler cmplr;
      environ::creflectionptr reflect;
      cscriptbuilder();
      struct cscriptbuilder& importfile(std::string path);
      struct cscriptbuilder& declbuiltin(std::string name,int nargs,
		       builtinfuncs::cbasicptr func);
      struct cscriptbuilder& enableconsoleinput();
      struct cscriptbuilder& enableconsoleoutput();
      struct cscriptbuilder& enablebasics();
      interpreter::cinterpreterptr finalize();
    };
  }
}

#endif//LISP_SCRIPT_SCRIPTBUILDER_HPP_
