#include "reflection.hpp"
#include "../compiler/exception.hpp"

namespace lisp{
  namespace environ{
    creflection::creflection(cenvironptr environ):environ(environ){
    }
    int creflection::rsrvfunc(std::string name,int nargs){
      if(!funcs.count(name)){
	funcs[name]=environ->rsrvfunc();
	funcnargs[name]=nargs;
      }else if((funcnargs[name]!=-1)&&(funcnargs[name]!=nargs)){
	throw compiler::exception::mismatched_arguments(name,funcnargs[name],nargs);
      }
      return funcs[name];
    }
    int creflection::declfunc(std::string name,int nargs,
			      function::cfunctionptr func){
      int id=rsrvfunc(name,nargs);
      if(!environ->functions[id].isnull()){
	throw compiler::exception::redeclared_function(name);
      }
      return environ->declfunc(id,func);
    }
  }
}
