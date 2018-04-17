#include "globals.hpp"

namespace lisp{
  namespace interpreter{
    cglobals::cglobals(unsigned int size){
      for(unsigned int i=0;i<size;i++){
	globals.push_back(new val::cnil());
      }
    }
  }
}
