#ifndef LISP_ENVIRON_ENVIRON_HPP_
#define LISP_ENVIRON_ENVIRON_HPP_

#include <vector>
#include "../function/function.hpp"
#include "../../util/refcntptrmod.hpp"

namespace lisp{
  namespace environ{
    struct cenviron{
      std::vector<function::cfunctionptr> functions;
      unsigned int globalscnt;
      cenviron();
      int rsrvfunc();
      int declfunc(int id,function::cfunctionptr func);
    };
    typedef util::crefcntptrmod<struct cenviron> cenvironptr;
  }
}

#endif//LISP_ENVIRON_ENVIRON_HPP_
