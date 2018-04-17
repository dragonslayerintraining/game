#ifndef LISP_COMPILER_HPP_
#define LISP_COMPILER_HPP_

#include "../val/val.hpp"
#include "../environ/environ.hpp"
#include "../errlog/errlog.hpp"
#include "symtab.hpp"
#include "../bytecode/bytecode.hpp"

namespace lisp{
  namespace compiler{
    struct ccompiler{
      environ::cenvironptr environ;
      errlog::cerrlogptr errlog;
      struct csymtab symtab;
      ccompiler(environ::cenvironptr environ,
		errlog::cerrlogptr errlog);
      std::ostream& error(val::cvalptr where);
      void enterscope(int numvars,bytecode::cbytecodeptr code);
      void exitscope(int numvars,bytecode::cbytecodeptr code);
      bool loadvar(std::string name,bytecode::cbytecodeptr code,
		   val::cvalptr where);
      bool storevar(std::string name,bytecode::cbytecodeptr code,
		    val::cvalptr where);
      void compileglobal(val::cvalptr expr);
      void compileexpr(val::cvalptr expr,bytecode::cbytecodeptr bytecode);
      void finalize();
    };
  }
}

#endif//LISP_COMPILER_HPP_
