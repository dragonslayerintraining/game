#ifndef UTIL_REFCNTPTRCONST_HPP_
#define UTIL_REFCNTPTRCONST_HPP_

#include <algorithm>

namespace util{
  template<class T>
  struct crefcntptrconst;
  template<class T>
  class crefcntptrconsthelper{
    friend class crefcntptrconst<T>;
    int refcnt;
    T* ptr;
    crefcntptrconsthelper(T* ptr):refcnt(1),ptr(ptr){
    }
    void addref(){
      refcnt++;
    }
    void delref(){
      if(--refcnt==0){
	delete ptr;
	delete this;
      }
    }
  };
  template<class T>
  class crefcntptrconst{
    T* ptr;
    class crefcntptrconsthelper<T>* helper;
  public:
    crefcntptrconst():
      ptr(NULL),helper(new crefcntptrconsthelper<T>(NULL)){
    }
    crefcntptrconst(T* ptr):
      ptr(ptr),helper(new crefcntptrconsthelper<T>(ptr)){
    }
    crefcntptrconst(const crefcntptrconst& other):
      ptr(other.ptr),helper(other.helper){
      helper->addref();
    }
    void swap(crefcntptrconst& other){
      std::swap(ptr,other.ptr);
      std::swap(helper,other.helper);
    }
    void clear(){
      crefcntptrconst<T>(NULL).swap(*this);
    }
    struct crefcntptrconst<T>& operator=(struct crefcntptrconst<T> other){
      swap(other);
      return *this;
    }
    const T& operator*()const{
      return *ptr;
    }
    const T* operator->()const{
      return ptr;
    }
    bool isnull(){
      return (ptr==NULL);
    }
    ~crefcntptrconst(){
      helper->delref();
    }
  };
}

#endif//UTIL_REFCNTPTRCONST_HPP_
