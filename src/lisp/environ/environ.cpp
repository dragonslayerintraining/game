#include "environ.hpp"
#include "../function/bytecodefunc.hpp"

namespace lisp{
  namespace environ{
    cenviron::cenviron():globalscnt(0){
    }
    int cenviron::rsrvfunc(){
      int id=functions.size();
      functions.push_back(NULL);
      return id;
    }
    int cenviron::declfunc(int id,function::cfunctionptr func){
      functions[id]=func;
      return id;
    }
  }
}
