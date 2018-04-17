#ifndef LISP_COMPILER_SYMTAB_HPP_
#define LISP_COMPILER_SYMTAB_HPP_

#include "../environ/environ.hpp"
#include "../environ/reflection.hpp"
#include "../bytecode/bytecode.hpp"
#include "scope.hpp"

namespace lisp{
  namespace compiler{
    struct csymtab{
      environ::cenvironptr environ;
      environ::creflectionptr reflect;
      struct cglobalscope* globals;
      struct clocalscope* locals;
      csymtab(environ::cenvironptr environ);
      csymtab(environ::cenvironptr environ,environ::creflectionptr reflect);
      ~csymtab();
      void pushscope();
      void popscope();
      int rsrvfunc(std::string name,int nargs);
      int declfunc(std::string name,int nargs,function::cfunctionptr func);
      int declfunc(std::string name,int nargs,bytecode::cbytecodeptr code);
    };
  }
}

#endif//LISP_COMPILER_SYMTAB_HPP_
