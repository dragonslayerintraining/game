#ifndef LISP_INTERPRETER_EXCEPTION_HPP_
#define LISP_INTERPRETER_EXCEPTION_HPP_

#include <stdexcept>

namespace lisp{
  namespace interpreter{
    namespace exception{
      struct exception: public std::exception{
	explicit exception()throw();
	const char* what()const throw();
	virtual ~exception()throw();
      };
      struct reflection_disabled: public exception{
	explicit reflection_disabled()throw();
	const char* what()const throw();
	~reflection_disabled()throw();
      };
    }
  }
}

#endif//LISP_INTERPRETER_EXCEPTION_HPP_
