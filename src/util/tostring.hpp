#ifndef UTIL_TOSTRING_HPP_
#define UTIL_TOSTRING_HPP_

#include <string>
#include <sstream>

namespace util{
  template<class T>
  std::string tostring(T obj){
    std::ostringstream ss;
    ss<<obj;
    return ss.str();
  }
}

#endif//UTIL_TOSTRING_HPP_
