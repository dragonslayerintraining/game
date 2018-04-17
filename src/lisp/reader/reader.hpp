#ifndef LISP_READER_READER_HPP_
#define LISP_READER_READER_HPP_

#include "../val/val.hpp"
#include <istream>
#include <vector>

namespace lisp{
  namespace reader{
    namespace exception{
      struct exception: public std::exception{
	explicit exception()throw();
	const char* what()const throw();
	virtual ~exception()throw();
      };
      struct unexpected_eof: public exception{
	explicit unexpected_eof()throw();
	const char* what()const throw();
      };
      struct input_failed: public exception{
	explicit input_failed()throw();
	const char* what()const throw();
      };
      struct bad_number: public exception{
	int line;
	std::string str;
	explicit bad_number(int line,std::string str)throw();
	const char* what()const throw();
	virtual ~bad_number()throw();
      };
      struct mismatched_parenthesis: public exception{
	int line;
	explicit mismatched_parenthesis(int line)throw();
	const char* what()const throw();
      };
      struct stray_char: public exception{
	int line;
	char c;
	explicit stray_char(int line,char c)throw();
	const char* what()const throw();
      };
    }
    val::cvalptr read(std::istream& in);
    std::vector<val::cvalptr> readall(std::istream& in);
  }
}

#endif//LISP_READER_READER_HPP_
