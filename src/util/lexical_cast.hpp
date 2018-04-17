#ifndef UTIL_LEXICAL_CAST_HPP_
#define UTIL_LEXICAL_CAST_HPP_

#include <stdexcept>
#include <sstream>

namespace util{
  struct bad_lexical_cast: public std::exception{
    explicit bad_lexical_cast()throw();
    const char* what()const throw();
    ~bad_lexical_cast()throw();
  };
  template<class T>
  T lexical_cast(std::string str){
    std::istringstream ss(str);
    T ret;
    ss>>ret;
    if(ss.bad()||!ss.eof()){
      throw bad_lexical_cast();
    }
    return ret;
  }
}

#endif//UTIL_LEXICAL_CAST_HPP_
