#include "basicfunc.hpp"

#include <iostream>

namespace lisp{
  namespace function{
    cbasicfunc::cbasicfunc(builtinfuncs::cbasicptr func):func(func){
    }
    void cbasicfunc::call(struct interpreter::cruntimeenv& rte,
			  unsigned int nargs){
      std::vector<val::cvalptr> args;
      args.insert(args.end(),rte.stk.end()-nargs,rte.stk.end());
      rte.stk.erase(rte.stk.end()-nargs,rte.stk.end());
      rte.stk.push_back(func->call(args));
    }
  }
}
