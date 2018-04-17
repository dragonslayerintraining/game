#include "exception.hpp"

namespace lisp{
  namespace compiler{
    namespace exception{
      exception::exception()throw(){
      }
      const char* exception::what()const throw(){
	return "Compiler exception";
      }
      exception::~exception()throw(){
      }
      undeclared_variable::undeclared_variable(std::string name)throw():
	name(name){
      }
      const char* undeclared_variable::what()const throw(){
	return "Error: Undeclared variable";
      }
      undeclared_variable::~undeclared_variable()throw(){
      }
      redeclared_variable::redeclared_variable(std::string name)throw():
	name(name){
      }
      const char* redeclared_variable::what()const throw(){
	return "Error: Redeclared variable";
      }
      redeclared_variable::~redeclared_variable()throw(){
      }
      undeclared_function::undeclared_function(std::string name)throw():
	name(name){
      }
      const char* undeclared_function::what()const throw(){
	return "Error: Undeclared function";
      }
      undeclared_function::~undeclared_function()throw(){
      }
      redeclared_function::redeclared_function(std::string name)throw():
	name(name){
      }
      const char* redeclared_function::what()const throw(){
	return "Error: Redeclared function";
      }
      redeclared_function::~redeclared_function()throw(){
      }
      mismatched_arguments::mismatched_arguments(std::string name,
						 int nargs1,int nargs2)throw():
	name(name),nargs1(nargs1),nargs2(nargs2){
      }
      const char* mismatched_arguments::what()const throw(){
	return "Error: Redeclared function";
      }
      mismatched_arguments::~mismatched_arguments()throw(){
      }
    }
  }
}
