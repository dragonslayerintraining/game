#ifndef LISP_BYTECODE_HPP_
#define LISP_BYTECODE_HPP_

#include "../../util/refcntptrmod.hpp"
#include "../val/val.hpp"
#include <vector>
#include <map>

namespace lisp{
  namespace bytecode{
    namespace instr{
      struct ivisitor;
      struct iinstr{
	virtual void accept(struct ivisitor& visitor)const=0;
	virtual ~iinstr();
      };
      typedef util::crefcntptrconst<struct iinstr> cinstrptr;

      struct cconst: public iinstr{
	val::cvalptr val;
	cconst(val::cvalptr val);
	void accept(struct ivisitor& visitor)const;
      };
      struct cpop: public iinstr{
	cpop();
	void accept(struct ivisitor& visitor)const;
      };
      struct cdup: public iinstr{
	cdup();
	void accept(struct ivisitor& visitor)const;
      };
      struct creservelocal: public iinstr{
	int numvars;
	creservelocal(int numvars);
	void accept(struct ivisitor& visitor)const;
      };
      struct cfreelocal: public iinstr{
	int numvars;
	cfreelocal(int numvars);
	void accept(struct ivisitor& visitor)const;
      };
      struct cloadlocal: public iinstr{
	int id;
	cloadlocal(int id);
	void accept(struct ivisitor& visitor)const;
      };
      struct cstorelocal: public iinstr{
	int id;
	cstorelocal(int id);
	void accept(struct ivisitor& visitor)const;
      };
      struct cloadglobal: public iinstr{
	int id;
	cloadglobal(int id);
	void accept(struct ivisitor& visitor)const;
      };
      struct cstoreglobal: public iinstr{
	int id;
	cstoreglobal(int id);
	void accept(struct ivisitor& visitor)const;
      };
      struct cjump: public iinstr{
	int label;
	cjump(int label);
	void accept(struct ivisitor& visitor)const;
      };
      struct cjnz: public iinstr{
	int label;
	cjnz(int label);
	void accept(struct ivisitor& visitor)const;
      };
      struct cjz: public iinstr{
	int label;
	cjz(int label);
	void accept(struct ivisitor& visitor)const;
      };
      struct ccallfunc: public iinstr{
	int id;
	int nargs;
	ccallfunc(int id,int nargs);
	void accept(struct ivisitor& visitor)const;
      };
      struct ivisitor{
	virtual void visit(const struct cconst& instr)=0;
	virtual void visit(const struct cpop& instr)=0;
	virtual void visit(const struct cdup& instr)=0;
	virtual void visit(const struct creservelocal& instr)=0;
	virtual void visit(const struct cfreelocal& instr)=0;
	virtual void visit(const struct cloadlocal& instr)=0;
	virtual void visit(const struct cstorelocal& instr)=0;
	virtual void visit(const struct cloadglobal& instr)=0;
	virtual void visit(const struct cstoreglobal& instr)=0;
	virtual void visit(const struct cjump& instr)=0;
	virtual void visit(const struct cjnz& instr)=0;
	virtual void visit(const struct cjz& instr)=0;
	virtual void visit(const struct ccallfunc& instr)=0;
	~ivisitor();
      };
    }
    struct cbytecode{
      std::vector<instr::cinstrptr> code;
      std::map<int,int> labels;
      int nextlabel;
      cbytecode();
      int newlabel();
      void placelabel(int label);
      void append(instr::cinstrptr instr);
      void dump();
    };
    typedef util::crefcntptrmod<struct cbytecode> cbytecodeptr;
  }
}

#endif//LISP_BYTECODE_HPP_
