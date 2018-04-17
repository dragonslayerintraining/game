#include "scope.hpp"
#include "exception.hpp"

namespace lisp{
  namespace compiler{
    cglobalscope::cglobalscope(){
    }
    bool cglobalscope::hasvar(std::string name){
      return idents.count(name);
    }
    int cglobalscope::findvar(std::string name){
      if(!idents.count(name)){
	throw exception::undeclared_variable(name);
      }
      return idents[name];
    }
    int cglobalscope::declvar(std::string name){
      if(idents.count(name)){
	throw exception::redeclared_variable(name);
      }
      int id=idents.size();
      idents[name]=id;
      return id;
    }

    clocalscope::clocalscope():
      parent(NULL),nextid(0){
    }
    clocalscope::clocalscope(struct clocalscope* parent):
      parent(parent),nextid(parent->nextid){
    }
    bool clocalscope::hasvar(std::string name){
      if(idents.count(name)){
	return true;
      }
      if(parent==NULL){
	return false;
      }
      return parent->hasvar(name);
    }
    int clocalscope::findvar(std::string name){
      if(idents.count(name)){
	return idents[name];
      }
      if(parent==NULL){
	throw exception::undeclared_variable(name);
      }
      return parent->findvar(name);
    }
    int clocalscope::declvar(std::string name){
      if(idents.count(name)){
	throw exception::redeclared_variable(name);
      }
      idents[name]=nextid++;
      return idents[name];
    }
    struct clocalscope* clocalscope::subscope(){
      return new clocalscope(this);
    }
    struct clocalscope* clocalscope::parentscope(){
      return parent;
    }
  }
}
