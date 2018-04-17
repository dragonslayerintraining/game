#include "lexical_cast.hpp"

namespace util{
  bad_lexical_cast::bad_lexical_cast()throw(){
  }
  const char* bad_lexical_cast::what()const throw(){
    return "Bad lexical cast";
  }
  bad_lexical_cast::~bad_lexical_cast()throw(){
  }
}
