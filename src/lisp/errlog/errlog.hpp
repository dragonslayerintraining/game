#ifndef LISP_ERRLOG_HPP_
#define LISP_ERRLOG_HPP_

#include <ostream>
#include "../../util/refcntptrmod.hpp"

namespace lisp{
  namespace errlog{
    struct cerrlog{
      int errcnt;
      cerrlog();
      std::ostream& error();
    };
    typedef util::crefcntptrmod<struct cerrlog> cerrlogptr;
  }
}

#endif//LISP_ERRLOG_HPP_
