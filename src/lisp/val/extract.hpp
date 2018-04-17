#ifndef LISP_VAL_EXTRACT_HPP_
#define LISP_VAL_EXTRACT_HPP_

#include "val.hpp"
#include <vector>

namespace lisp{
  namespace val{
    namespace extract{
      struct cnilvisitor: public ivisitor{
	bool success;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct cpairvisitor: public ivisitor{
	bool success;
	cvalptr first,rest;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct cintvisitor: public ivisitor{
	bool success;
	int ret;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct cdblvisitor: public ivisitor{
	bool success;
	double ret;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct cstrvisitor: public ivisitor{
	bool success;
	std::string ret;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct cidentvisitor: public ivisitor{
	bool success;
	std::string ret;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct cboolvisitor: public ivisitor{
	bool ret;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct cnumbervisitor: public ivisitor{
	bool success;
	bool isint,isdbl;
	int intval;
	double dblval;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
      struct clistvisitor: public ivisitor{
	bool success;
	std::vector<cvalptr> list;
	void visit(const struct cnil& var);
	void visit(const struct cpair& var);
	void visit(const struct cint& var);
	void visit(const struct cdbl& var);
	void visit(const struct cstr& var);
	void visit(const struct cident& var);
      };
    }
  }
}

#endif//LISP_VAL_EXTRACT_HPP_

