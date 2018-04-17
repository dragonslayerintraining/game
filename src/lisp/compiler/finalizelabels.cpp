#include "finalizelabels.hpp"

namespace lisp{
  namespace compiler{
    struct cfinalizelabelsvisitor: public bytecode::instr::ivisitor{
      bytecode::cbytecodeptr ret;
      std::map<int,int> labels;
      cfinalizelabelsvisitor(bytecode::cbytecodeptr old):
	ret(new bytecode::cbytecode()),labels(old->labels){
      }
      void visit(const struct bytecode::instr::cconst& instr){
	ret->append(new bytecode::instr::cconst(instr.val));
      }
      void visit(const struct bytecode::instr::cpop& instr){
	(void)instr;
	ret->append(new bytecode::instr::cpop());
      }
      void visit(const struct bytecode::instr::cdup& instr){
	(void)instr;
	ret->append(new bytecode::instr::cdup());
      }
      void visit(const struct bytecode::instr::creservelocal& instr){
	ret->append(new bytecode::instr::creservelocal(instr.numvars));
      }
      void visit(const struct bytecode::instr::cfreelocal& instr){
	ret->append(new bytecode::instr::cfreelocal(instr.numvars));
      }
      void visit(const struct bytecode::instr::cloadlocal& instr){
	ret->append(new bytecode::instr::cloadlocal(instr.id));
      }
      void visit(const struct bytecode::instr::cstorelocal& instr){
	ret->append(new bytecode::instr::cstorelocal(instr.id));
      }
      void visit(const struct bytecode::instr::cloadglobal& instr){
	ret->append(new bytecode::instr::cloadglobal(instr.id));
      }
      void visit(const struct bytecode::instr::cstoreglobal& instr){
	ret->append(new bytecode::instr::cstoreglobal(instr.id));
      }
      void visit(const struct bytecode::instr::cjump& instr){
	ret->append(new bytecode::instr::cjump(labels[instr.label]));
      }
      void visit(const struct bytecode::instr::cjnz& instr){
	ret->append(new bytecode::instr::cjnz(labels[instr.label]));
      }
      void visit(const struct bytecode::instr::cjz& instr){
	ret->append(new bytecode::instr::cjz(labels[instr.label]));
      }
      void visit(const struct bytecode::instr::ccallfunc& instr){
	ret->append(new bytecode::instr::ccallfunc(instr.id,instr.nargs));
      }
    };
    bytecode::cbytecodeptr finalizelabels(bytecode::cbytecodeptr code){
      struct cfinalizelabelsvisitor visitor(code);
      for(unsigned int i=0;i<code->code.size();i++){
	code->code[i]->accept(visitor);
      }
      return visitor.ret;
    }
  }
}
