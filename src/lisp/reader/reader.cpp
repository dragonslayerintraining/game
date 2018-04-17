#include "reader.hpp"
#include "../val/matcher.hpp"
#include <cctype>
#include <vector>
#include <algorithm>
#include <sstream>

#include <iostream>

namespace lisp{
  namespace reader{
    namespace exception{
      exception::exception()throw(){
      }
      const char* exception::what()const throw(){
	return "Reader: Error";
      }
      exception::~exception()throw(){
      }
      unexpected_eof::unexpected_eof()throw(){
      }
      const char* unexpected_eof::what()const throw(){
	return "Reader: Unexpected EOF";
      }
      input_failed::input_failed()throw(){
      }
      const char* input_failed::what()const throw(){
	return "Reader: Input failed";
      }
      bad_number::bad_number(int line,std::string str)throw():
	line(line),str(str){
      }
      const char* bad_number::what()const throw(){
	return "Reader: Bad number";
      }
      bad_number::~bad_number()throw(){
      }
      mismatched_parenthesis::mismatched_parenthesis(int line)throw():
	line(line){
      }
      const char* mismatched_parenthesis::what()const throw(){
	return "Reader: Mismatched parenthesis";
      }
      stray_char::stray_char(int line,char c)throw():
	line(line),c(c){
      }
      const char* stray_char::what()const throw(){
	return "Reader: Stray character in program";
      }
    }
    struct cparser{
      std::istream& in;
      int line;
      cparser(std::istream& in):in(in),line(1){
      }
    private:
      void checkin(){
	if(in.eof()){
	  throw exception::unexpected_eof();
	}
	if(in.fail()){
	  throw exception::input_failed();
	}
      }
      void skipcomments(){
	if(in.peek()==';'){
	  while(in.good()&&(in.get()!='\n'));
	}
      }
      char eat(){
	skipcomments();
	return in.get();
      }
      char peek(){
	skipcomments();
	return in.peek();
      }
      bool match(char c){
	return (peek()==c);
      }
      bool match_and_eat(char c){
	if(peek()==c){
	  eat();
	  return true;
	}
	return false;
      }
    public:
      void skipspaces(){
	while(in.good()&&std::isspace(peek())){
	  if(eat()=='\n'){
	    line++;
	  }
	}
      }
    public:
      val::cvalptr parse(){
	skipspaces();
	checkin();
	std::vector<val::cvalptr> children;
	if(match_and_eat('(')){
	  skipspaces();
	  while(!match_and_eat(')')){
	    checkin();
	    children.push_back(parse());
	    skipspaces();
	  }
	  if(children.size()==3){
	    val::matcher::cmatcherptr matcher=
	      new val::matcher::cidentmatcher(".");
	    if(matcher->matches(children[1])){
	      return new val::cpair(children[0],children[2]);
	    }
	  }


	  val::cvalptr ret=new val::cnil();
	  for(int i=children.size()-1;i>=0;i--){
	    ret=new val::cpair(children[i],ret);
	  }
	  return ret;
	}
	if(match_and_eat('\'')){
	  return new val::cpair(new val::cident("quote"),
				new val::cpair(parse(),
					       new val::cnil()));
	}
	if(std::isdigit(peek())||match('+')||match('-')||match('.')){
	  std::string str;
	  if(match('+')||match('-')){
	    str+=eat();
	  }
	  if(!(std::isdigit(peek())||match('.'))){
	    //must be '+' or '-'
	    return new val::cident(str);
	  }
	  int cnt=0;
	  while(std::isdigit(peek())||match('.')){
	    if(match('.')){
	      cnt++;
	    }
	    str+=eat();
	  }
	  if(str=="."){
	    return new val::cident(str);
	  }
	  switch(cnt){
	  case 0:
	    {
	      int num;
	      std::istringstream ss(str);
	      ss>>num;
	      return new val::cint(num);
	    }
	  case 1:
	    {
	      double num;
	      std::istringstream ss(str);
	      ss>>num;
	      return new val::cdbl(num);
	    }
	  default:
	    throw exception::bad_number(line,str);
	  }
	}
	if(match_and_eat('"')){
	  std::string str;
	  while(!match_and_eat('"')){
	    checkin();
	    match_and_eat('\\');
	    str+=eat();
	  }
	  return new val::cstr(str);
	}
	if(match_and_eat(')')){
	  throw exception::mismatched_parenthesis(line);
	}
	std::string str;
	while(std::isgraph(peek())&&
	      !match('(')&&!match(')')&&!match('\'')&&!match('"')){
	  checkin();
	  match_and_eat('\\');
	  str+=eat();
	}
	if(str.length()>0){
	  return new val::cident(str);
	}
	throw exception::stray_char(line,eat());
      }
    };
    val::cvalptr read(std::istream& in){
      struct cparser parser(in);
      return parser.parse();
    }
    std::vector<val::cvalptr> readall(std::istream& in){
      struct cparser parser(in);
      std::vector<val::cvalptr> ret;
      while(!in.eof()){
	ret.push_back(parser.parse());
	parser.skipspaces();
      }
      return ret;
    }
  }
}
