#include "exception.hpp"

namespace lisp{
  namespace interpreter{
    namespace exception{
      exception::exception()throw(){
      }
      const char* exception::what()const throw(){
	return "Interpreter exception";
      }
      exception::~exception()throw(){
      }
      reflection_disabled::reflection_disabled()throw(){
      }
      const char* reflection_disabled::what()const throw(){
	return "Error: Reflection is not enabled";
      }
      reflection_disabled::~reflection_disabled()throw(){
      }
    }
  }
}
