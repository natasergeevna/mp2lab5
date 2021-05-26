#pragma once
#include <iostream>
#include <cstring>
#include "stack.h"

class TTextNode
{
protected:
  static TTextNode* firstFree; 
  static TTextNode* textNodes;

  TTextNode* next; 
  TTextNode* down; 
  char c; 
  int level; //0 - текст, 1 - строка, 2 - слово, 3 - буква

public:
  TTextNode(int _l = 3, char _c = 0);
  TTextNode(char* s, int _l); 
  TTextNode(const TTextNode& _node); 
  ~TTextNode();

  TTextNode* GetNext();
  TTextNode* GetDown();
  char GetC();
  int GetLevel();

  void SetNext(TTextNode* _next);
  void SetDown(TTextNode* _down);
  void SetC(char _c);
  void SetLevel(int _l);

  friend std::ostream& operator<<(std::ostream& o, TTextNode& t);

  static void InitMem(int _size = 3); 
  static void FreeMem(); 

  void* operator new(size_t size);
  void operator delete(void* p);
};

TTextNode* TTextNode::firstFree = nullptr;
TTextNode* TTextNode::textNodes = nullptr;

std::ostream& operator<<(std::ostream& o, TTextNode& t)
{
  if (t.level == 3)
  {
    o << t.c;
    if (t.next != nullptr)
      o << *(t.next);
  }
  else
  {
    if (t.down != nullptr)
      o << *(t.down);

    if (t.next != nullptr)
      o << *(t.next);
  }

  return o;
}

TTextNode::TTextNode(int _l, char _c)
{
  next = nullptr;
  down = nullptr;
  c = _c;
  level = _l;
}

TTextNode::TTextNode(char* s, int l) //Принимает слово
{
  next = nullptr;
  c = 0;
  level = l;
  down = nullptr;

  if (l < 1 || l > 3)
    throw std::exception();
  if (l == 1)
  {
    int sz = strlen(s);
    if (sz > 0) {
      int start = 0;
      TTextNode* wcur = new TTextNode(2);
      this->SetDown(wcur);
      for (int i = 0; i < sz; i++) {
        if (s[i] == ' ' || i == sz - 1)
        {
          if (start != 0) {
            wcur->SetNext(new TTextNode(2));
            wcur = wcur->GetNext();
          }
          TTextNode* lcur = new TTextNode(3, s[start]);
          wcur->SetDown(lcur);
          for (int j = start + 1; j <= i; j++) {
            lcur->SetNext(new TTextNode(3, s[j]));
            lcur = lcur->GetNext();
          }
          lcur->SetNext(nullptr);
          start = i + 1;
        }
      }
      wcur->SetNext(nullptr);
    }
  }
  if (l == 2)
  {
    next = nullptr;
    c = 0;
    level = l;
    int sz = strlen(s);
    if (sz > 0) {
      TTextNode* lcur = new TTextNode(3, s[0]);
      this->SetDown(lcur);
      for (int i = 1; i < sz; i++) {
        lcur->SetNext(new TTextNode(3, s[i]));
        lcur = lcur->GetNext();
      }
      lcur->SetNext(nullptr);
    }
  }
  if (l == 3)
  {
    c = s[0];
    level = l;
    next = nullptr;
  }
}

TTextNode::TTextNode(const TTextNode& _node)
{
  next = nullptr;
  down = nullptr;
  c = _node.c;
  level = _node.level;
}

TTextNode::~TTextNode(){}

TTextNode* TTextNode::GetNext()
{
  return next;
}

TTextNode* TTextNode::GetDown()
{
  return down;
}

char TTextNode::GetC()
{
  return c;
}

int TTextNode::GetLevel()
{
  return level;
}

void TTextNode::SetNext(TTextNode* _next)
{
  next = _next;
}

void TTextNode::SetDown(TTextNode* _down)
{
  down = _down;
}

void TTextNode::SetC(char _c)
{
  c = _c;
}

void TTextNode::SetLevel(int _l)
{
  if (_l >= 1 && _l <= 3)
    level = _l;
  else
     throw "Error";
}

void TTextNode::InitMem(int _size)
{
  if (_size <= 0)
     throw "Error";

  if ((firstFree == nullptr) && (textNodes == nullptr))
  {
    textNodes = new TTextNode[_size];
    firstFree = textNodes;
  }
  else if ((firstFree != nullptr) && (textNodes == nullptr))
     throw "Error";

  else
    textNodes = new TTextNode[_size * 2];
  firstFree = textNodes;
}

void TTextNode::FreeMem() //Освобождение памяти
{
  if (textNodes != nullptr)
    delete[] textNodes;
  textNodes = nullptr;
  firstFree = nullptr;
}

void* TTextNode::operator new(size_t size)
{
  if ((firstFree == nullptr) && (textNodes == nullptr))
    InitMem();

  if ((firstFree == nullptr) && (textNodes != nullptr))
    InitMem();

  TTextNode* node = firstFree;
  firstFree = firstFree->next;
  node->next = nullptr;

  return node;
}

void TTextNode::operator delete(void* p)
{
  TTextNode* node = (TTextNode*)p;

  if ((firstFree == nullptr) && (textNodes == nullptr))
     throw "Error";

  node->next = nullptr;
  node->down = nullptr;
  node->c = 0;
  node->level = 3;

  node->next = firstFree;
  firstFree = node;
}