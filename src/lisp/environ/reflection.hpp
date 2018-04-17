#ifndef LISP_ENVIRON_REFLECTION_HPP_
#define LISP_ENVIRON_REFLECTION_HPP_

#include <map>
#include <string>
#include "../function/function.hpp"
#include "environ.hpp"
#include "../../util/refcntptrmod.hpp"

namespace lisp{
  namespace environ{
    struct creflection{
      cenvironptr environ;
      std::map<std::string,int> funcs;
      std::map<std::string,int> funcnargs;
      creflection(cenvironptr environ);
      int rsrvfunc(std::string name,int nargs);
      int declfunc(std::string name,int nargs,function::cfunctionptr func);
    };
    typedef util::crefcntptrmod<struct creflection> creflectionptr;
  }
}

#endif//LISP_ENVIRON_REFLECTION_HPP_
