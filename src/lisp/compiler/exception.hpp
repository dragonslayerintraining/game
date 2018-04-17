#ifndef LISP_COMPILER_EXCEPTION_HPP_
#define LISP_COMPILER_EXCEPTION_HPP_

#include <stdexcept>

namespace lisp{
  namespace compiler{
    namespace exception{
      struct exception: public std::exception{
	explicit exception()throw();
	const char* what()const throw();
	virtual ~exception()throw();
      };
      struct undeclared_variable: public exception{
	std::string name;
	explicit undeclared_variable(std::string name)throw();
	const char* what()const throw();
	~undeclared_variable()throw();
      };
      struct redeclared_variable: public exception{
	std::string name;
	explicit redeclared_variable(std::string name)throw();
	const char* what()const throw();
	~redeclared_variable()throw();
      };
      struct undeclared_function: public exception{
	std::string name;
	explicit undeclared_function(std::string name)throw();
	const char* what()const throw();
	~undeclared_function()throw();
      };
      struct redeclared_function: public exception{
	std::string name;
	explicit redeclared_function(std::string name)throw();
	const char* what()const throw();
	~redeclared_function()throw();
      };
      struct mismatched_arguments: public exception{
	std::string name;
	int nargs1,nargs2;
	explicit mismatched_arguments(std::string name,
				      int nargs1,int nargs2)throw();
	const char* what()const throw();
	~mismatched_arguments()throw();
      };
    }
  }
}

#endif//LISP_COMPILER_EXCEPTION_HPP_
