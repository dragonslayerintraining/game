#include "symtab.hpp"
#include "exception.hpp"
#include "../function/bytecodefunc.hpp"

namespace lisp{
  namespace compiler{
    csymtab::csymtab(environ::cenvironptr environ):
      environ(environ),
      reflect(new environ::creflection(environ)),
      globals(new cglobalscope()),locals(new clocalscope()){
    }
    csymtab::csymtab(environ::cenvironptr environ,
		     environ::creflectionptr reflect):
      environ(environ),
      reflect(reflect),
      globals(new cglobalscope()),locals(new clocalscope()){
    }
    csymtab::~csymtab(){
      delete globals;
      delete locals;
    }
    void csymtab::pushscope(){
      locals=new clocalscope(locals);
    }
    void csymtab::popscope(){
      struct clocalscope* old=locals;
      locals=locals->parent;
      delete old;
    }
    int csymtab::rsrvfunc(std::string name,int nargs){
      return reflect->rsrvfunc(name,nargs);
    }
    int csymtab::declfunc(std::string name,int nargs,
			  function::cfunctionptr func){
      return reflect->declfunc(name,nargs,func);
    }
    int csymtab::declfunc(std::string name,int nargs,
			  bytecode::cbytecodeptr code){
      return declfunc(name,nargs,new function::cbytecodefunc(code));
    }
  }
}
