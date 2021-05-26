#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
  int size;
  T* pStack;
  int indS;
  
public:
  TStack(int size = 100);
  TStack(const TStack<T>& _v);
  ~TStack();
  
  TStack<T>& operator =(const TStack<T>& _v);
  
  void Push(T d);
  T Get();
  
  inline int min_elem();
  inline int max_elem();

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TStack<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TStack<T1> &A);
  
  int IsEmpty(void) const;
  int IsFull(void) const;
  int GetSize();
};

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1> &A) 
{
  for (int i = 0; i < A.indS; i++)
    ostr << A.pStack[i] << endl;
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1> &A) 
{
  int count;
  istr >> count;
  for (int i = 0; i < A.count; i++)
  {
    T1 d;
    istr >> d;
    A.Push(d);
  }
  return istr;
}

template<class T>
inline TStack<T>::TStack(int size)
{
  if (size > 0)
  {
    this->size = size;
    pStack = new T[size];
    for (int i = 0; i < size; i++)
      pStack[i] = 0;
    this->indS = 0;
  }
  else
    throw "error";
}

template <class T>
TStack<T>::TStack(const TStack<T>& _v)
{
  size = _v.size;
  indS = _v.indS;
  pStack = new T [size];
  for (int i = 0; i < size;i = i + 1)
    pStack[i] = _v.pStack[i];
}

template <class T>
TStack<T>::~TStack()
{
  size = 0;
  if (pStack != 0)
    delete [] pStack;
  pStack = 0;
}

template<typename T>
inline int TStack<T>::max_elem()
{
  T res = pStack[0];
  for (int i = 1; i < size; i++)
    if (pStack[i] > res)
      res = pStack[i];
  return res;
}

template<typename T>
inline int TStack<T>::min_elem()
{
  T res = pStack[0];
  for (int i = 1; i < size; i++)
    if (pStack[i] < res)
      res = pStack[i];
  return res;
}

template <class T>
TStack<T>& TStack<T>::operator =(const TStack<T>& _v)
{
  if (this == &_v)
    return *this;

  this->size = _v.size;
  if (pStack != NULL)
    delete[] pStack;

  this->pStack = new T [size];
  for (int i = 0; i < size; i++)
    pStack[i] = _v.pStack[i];
  this->indS = _v.indS;
  return *this;
}

template<class T>
inline void TStack<T>::Push(T d)
{
  if (indS >= size || indS < 0)
    throw "error";

  pStack[indS] = d;
  indS++;
}

template<class T>
inline T TStack<T>::Get()
{
  if (indS == 0)
    throw "error";

  T d = pStack[indS-1];
  indS--;
  return d;
}

template<class T>
inline int TStack<T>::IsEmpty(void) const
{
  return indS == 0;
}

template<class T>
inline int TStack<T>::IsFull(void) const
{
  return indS == size;
}

template <class T>
int TStack<T>::GetSize()
{
  return size;
}
#endif //_STACK_H_