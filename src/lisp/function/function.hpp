#ifndef LISP_FUNCTION_HPP_
#define LISP_FUNCTION_HPP_

#include "../../util/refcntptrmod.hpp"

namespace lisp{
  namespace interpreter{
    struct cruntimeenv;
  }
  namespace function{
    struct ifunction{
      virtual void call(struct interpreter::cruntimeenv& env,
			unsigned int nargs)=0;
      virtual ~ifunction();
    };
    typedef util::crefcntptrmod<struct ifunction> cfunctionptr;
  }
}

#endif//LISP_FUNCTION_HPP_
