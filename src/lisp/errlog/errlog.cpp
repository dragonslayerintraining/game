#include "errlog.hpp"
#include <iostream>

namespace lisp{
  namespace errlog{
    cerrlog::cerrlog():errcnt(0){
    }
    std::ostream& cerrlog::error(){
      errcnt++;
      return std::cerr;
    }
  }
}
