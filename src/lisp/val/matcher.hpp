#ifndef LISP_VAL_MATCHER_HPP_
#define LISP_VAL_MATCHER_HPP_

#include "val.hpp"
#include "../../util/refcntptrmod.hpp"
#include <vector>

namespace lisp{
  namespace val{
    namespace matcher{
      struct imatcher{
	virtual bool matches(cvalptr val)=0;
	virtual ~imatcher();
      };
      typedef util::crefcntptrmod<struct imatcher> cmatcherptr;
      //deep match
      struct cnilmatcher: public imatcher{
	bool matches(cvalptr val);
      };
      struct cpairmatcher: public imatcher{
	cmatcherptr first,rest;
	cpairmatcher(cmatcherptr first,cmatcherptr rest);
	bool matches(cvalptr val);
      };
      struct cintmatcher: public imatcher{
	int val;
	cintmatcher(int val);
	bool matches(cvalptr val);
      };
      struct cdblmatcher: public imatcher{
	double val;
	cdblmatcher(double val);
	bool matches(cvalptr val);
      };
      struct cstrmatcher: public imatcher{
	std::string val;
	cstrmatcher(std::string val);
	bool matches(cvalptr val);
      };
      struct cidentmatcher: public imatcher{
	std::string val;
	cidentmatcher(std::string val);
	bool matches(cvalptr val);
      };
      //shallow match
      struct canynilmatcher: public imatcher{
	bool matches(cvalptr val);
      };
      struct canypairmatcher: public imatcher{
        cvalptr& first;
	cvalptr& rest;
	canypairmatcher(cvalptr& first,cvalptr& rest);
	bool matches(cvalptr val);
      };
      struct canyintmatcher: public imatcher{
	int& val;
	canyintmatcher(int& val);
	bool matches(cvalptr val);
      };
      struct canydblmatcher: public imatcher{
	double& val;
	canydblmatcher(double& val);
	bool matches(cvalptr val);
      };
      struct canystrmatcher: public imatcher{
	std::string& val;
	canystrmatcher(std::string& val);
	bool matches(cvalptr val);
      };
      struct canyidentmatcher: public imatcher{
	std::string& val;
	canyidentmatcher(std::string& val);
	bool matches(cvalptr val);
      };
      //misc
      struct cboolmatcher: public imatcher{
	bool val;
	cboolmatcher(bool val);
	bool matches(cvalptr val);
      };
      struct canyboolmatcher: public imatcher{
	bool& val;
	canyboolmatcher(bool& val);
	bool matches(cvalptr val);
      };
      struct canylistmatcher: public imatcher{
	std::vector<cvalptr>& val;
	canylistmatcher(std::vector<cvalptr>& val);
	bool matches(cvalptr val);
      };
      struct canymatcher: public imatcher{
	cvalptr& val;
	canymatcher(cvalptr& val);
	bool matches(cvalptr val);
      };
      struct cstorematcher: public imatcher{
	cmatcherptr m;
	cvalptr& val;
	cstorematcher(cmatcherptr m,cvalptr& val);
	bool matches(cvalptr val);
      };
      struct cormatcher: public imatcher{
	cmatcherptr m1,m2;
	int& index;
	cormatcher(cmatcherptr m1,cmatcherptr m2,int& index);
	bool matches(cvalptr val);
      };
    }
  }
}

#endif//LISP_VAL_MATCHER_HPP_
