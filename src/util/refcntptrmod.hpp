#ifndef UTIL_REFCNTPTRMOD_HPP_
#define UTIL_REFCNTPTRMOD_HPP_

#include <algorithm>

namespace util{
  template<class T>
  struct crefcntptrmod;
  template<class T>
  class crefcntptrmodhelper{
    friend class crefcntptrmod<T>;
    int refcnt;
    T* ptr;
    crefcntptrmodhelper(T* ptr):refcnt(1),ptr(ptr){
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
  class crefcntptrmod{
    T* ptr;
    class crefcntptrmodhelper<T>* helper;
  public:
    crefcntptrmod():
      ptr(NULL),helper(new crefcntptrmodhelper<T>(NULL)){
    }
    crefcntptrmod(T* ptr):
      ptr(ptr),helper(new crefcntptrmodhelper<T>(ptr)){
    }
    crefcntptrmod(const crefcntptrmod& other):
      ptr(other.ptr),helper(other.helper){
      helper->addref();
    }
    void swap(crefcntptrmod& other){
      std::swap(ptr,other.ptr);
      std::swap(helper,other.helper);
    }
    void clear(){
      crefcntptrmod<T>(NULL).swap(*this);
    }
    struct crefcntptrmod<T>& operator=(struct crefcntptrmod<T> other){
      swap(other);
      return *this;
    }
    T& operator*(){
      return *ptr;
    }
    const T& operator*()const{
      return *ptr;
    }
    T* operator->(){
      return ptr;
    }
    const T* operator->()const{
      return ptr;
    }
    bool isnull(){
      return (ptr==NULL);
    }
    ~crefcntptrmod(){
      helper->delref();
    }
  };
}

#endif//UTIL_REFCNTPTRMOD_HPP_
