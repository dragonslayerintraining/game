#ifndef LISP_COMPILER_SCOPE_HPP_
#define LISP_COMPILER_SCOPE_HPP_

#include <string>
#include <map>

namespace lisp{
  namespace compiler{
    struct cglobalscope{
      std::map<std::string,int> idents;
      cglobalscope();
      bool hasvar(std::string name);
      int findvar(std::string name);
      int declvar(std::string name);
    };
    struct clocalscope{
      struct clocalscope* parent;
      std::map<std::string,int> idents;
      int nextid;
      clocalscope();
      clocalscope(struct clocalscope* parent);
      bool hasvar(std::string name);
      int findvar(std::string name);
      int declvar(std::string name);
      struct clocalscope* subscope();
      struct clocalscope* parentscope();
    };
  }
}

#endif//LISP_COMPILER_SCOPE_HPP_
