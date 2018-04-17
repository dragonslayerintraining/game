#include "bytecode.hpp"
#include "../val/tostr.hpp"
#include <iostream>

namespace lisp{
  namespace bytecode{
    namespace instr{
      iinstr::~iinstr(){
      }
      cconst::cconst(val::cvalptr val):val(val){
      }
      void cconst::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cpop::cpop(){
      }
      void cpop::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cdup::cdup(){
      }
      void cdup::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      creservelocal::creservelocal(int numvars):numvars(numvars){
      }
      void creservelocal::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cfreelocal::cfreelocal(int numvars):numvars(numvars){
      }
      void cfreelocal::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cloadlocal::cloadlocal(int id):id(id){
      }
      void cloadlocal::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cstorelocal::cstorelocal(int id):id(id){
      }
      void cstorelocal::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cloadglobal::cloadglobal(int id):id(id){
      }
      void cloadglobal::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cstoreglobal::cstoreglobal(int id):id(id){
      }
      void cstoreglobal::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cjump::cjump(int label):label(label){
      }
      void cjump::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cjnz::cjnz(int label):label(label){
      }
      void cjnz::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      cjz::cjz(int label):label(label){
      }
      void cjz::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      ccallfunc::ccallfunc(int id,int nargs):id(id),nargs(nargs){
      }
      void ccallfunc::accept(struct ivisitor& visitor)const{
	visitor.visit(*this);
      }
      ivisitor::~ivisitor(){
      }
    }
    cbytecode::cbytecode():nextlabel(0){
      newlabel();
    }
    int cbytecode::newlabel(){
      return nextlabel++;
    }
    void cbytecode::placelabel(int label){
      labels[label]=code.size();
    }
    void cbytecode::append(instr::cinstrptr instr){
      code.push_back(instr);
    }
    struct cdumpvisitor: public instr::ivisitor{
      void visit(const struct instr::cconst& instr){
	struct val::ctostrvisitor tostr;
	instr.val->accept(tostr);
	std::cerr<<"\tconst "<<tostr.getstr()<<std::endl;
      }
      void visit(const struct instr::cpop& instr){
	(void)instr;
	std::cerr<<"\tpop"<<std::endl;
      }
      void visit(const struct instr::cdup& instr){
	(void)instr;
	std::cerr<<"\tdup"<<std::endl;
      }
      void visit(const struct instr::creservelocal& instr){
	std::cerr<<"\treservelocal "<<instr.numvars<<std::endl;
      }
      void visit(const struct instr::cfreelocal& instr){
	std::cerr<<"\tfreelocal "<<instr.numvars<<std::endl;
      }
      void visit(const struct instr::cloadlocal& instr){
	std::cerr<<"\tloadlocal $"<<instr.id<<std::endl;
      }
      void visit(const struct instr::cstorelocal& instr){
	std::cerr<<"\tstorelocal $"<<instr.id<<std::endl;
      }
      void visit(const struct instr::cloadglobal& instr){
	std::cerr<<"\tloadglobal $"<<instr.id<<std::endl;
      }
      void visit(const struct instr::cstoreglobal& instr){
	std::cerr<<"\tstoreglobal $"<<instr.id<<std::endl;
      }
      void visit(const struct instr::cjump& instr){
	std::cerr<<"\tjump @"<<instr.label<<std::endl;
      }
      void visit(const struct instr::cjnz& instr){
	std::cerr<<"\tjnz @"<<instr.label<<std::endl;
      }
      void visit(const struct instr::cjz& instr){
	std::cerr<<"\tjz @"<<instr.label<<std::endl;
      }
      void visit(const struct instr::ccallfunc& instr){
	std::cerr<<"\tcall %"<<instr.id<<","<<instr.nargs<<std::endl;
      }
    };
    void cbytecode::dump(){
      std::map<int,int> invlabels;
      for(std::map<int,int>::iterator it=labels.begin();it!=labels.end();it++){
	invlabels[it->second]=it->first;
      }
      struct cdumpvisitor dumper;
      for(unsigned int i=0;i<code.size();i++){
	if(invlabels.count(i)){
	  std::cerr<<"@"<<invlabels[i];
	}else{
	  std::cerr<<i;
	}
	code[i]->accept(dumper);
      }
    }
  }
}
