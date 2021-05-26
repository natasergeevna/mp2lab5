#pragma once
#include "text_node.h"
#include <fstream>
#include <string>

class TTextIter;

class TText 
{
protected:
    TTextNode* root;
public:
    TText(char* s = 0);
    ~TText();

    TTextIter GetRoot(); 
    TTextIter Find(char c); 
    TTextIter Find(char* c); 
    TTextIter FindWord(char* c); 


    void Insert(char* c, TTextIter i);
    void InsertData(char* c, TTextIter i);
    void InsertLine(char* c, TTextIter iter);
    void Delete(int count, TTextIter i); 
    char* Copy(int count, TTextIter i); 

    friend std::ostream& operator<<(std::ostream& o, TText& t);
};

class TTextIter 
{
protected:
    TText& text;
    TTextNode* node;
    TStack<TTextNode*> st;
public:
    TTextIter() = default;
    TTextIter(TText& _text, TTextNode* _node, TStack<TTextNode*> _st);
    TTextIter(const TTextIter& t);

    bool GoNext(); 
    bool GoNextChar();
    bool IsEnd();

    void ResetToString();
    void ResetToWord();

    TTextNode* Get();    
};



TTextIter::TTextIter(TText& _text, TTextNode* _node, TStack<TTextNode*> _st) : text(_text)
{
  node = _node;
  st = _st;
}

TTextIter::TTextIter(const TTextIter& t) : text(t.text)
{
  node = t.node;
  st = t.st;
  text = t.text;
}

bool TTextIter::GoNext()
{
  if (node->GetLevel() == 3)
  {
    if (node->GetNext() != nullptr)
      node = node->GetNext();
    else
    {
      node = st.Get();
      if (node->GetNext() != nullptr)
        node = node->GetNext();
      else
      {
        node = st.Get();
        if (node->GetNext() != nullptr)
          node = node->GetNext();
        else
        {
          node = 0;
          return false;
        }
      }
    }
  }
  else
  {
    st.Push(node);
    node = node->GetDown();
  }
  return true;
}

bool TTextIter::GoNextChar()
{
  if (node->GetLevel() == 1)
  {
    if (node->GetDown() == nullptr)
      return false;
    else
    {
      st.Push(node);
      node = node->GetDown();
      st.Push(node);
      node = node->GetDown();
      return true;
    }
  }
  if (node->GetLevel() == 2)
  {
    if (node->GetDown() == nullptr)
      return false;
    else
    {
      st.Push(node);
      node = node->GetDown();
      return true;
    }
  }
  if (node->GetLevel() == 3 && node->GetNext() != nullptr)
  {
    if (node->GetNext() == nullptr)
      return false;
    else
    {
      node = node->GetNext();
      return true;

    }
  }

  if (node->GetLevel() == 3 && node->GetNext() == nullptr)
  {
    if (st.IsEmpty())
      throw "Error";

    TTextNode* temp = st.Get();

    if (temp->GetNext() != nullptr)
    {
      st.Push(temp->GetNext());
      node = temp->GetNext()->GetDown();
      return true;
    }

  }
  return false;
}

bool TTextIter::IsEnd()
{
  if (node == nullptr)
    return true;

  if (node->GetLevel() == 1 || node->GetLevel() == 2)
    return false;

  if (node->GetLevel() == 3 && node->GetNext() != nullptr)
    return false;

  if (node->GetLevel() == 3 && node->GetNext() == nullptr)
  {
    if (st.IsEmpty())
      throw "Error";

    TTextNode* prev = st.Get();
    if (prev->GetNext() != nullptr)
      return true;
  }

  return true;
}

void TTextIter::ResetToString()
{
  while (node->GetLevel() > 1) 
  {
    st.Get();
    if (st.IsEmpty())
      throw "Error";
    node = st.Get();
  }
}

void TTextIter::ResetToWord()
{
  if (node->GetLevel() == 1)
  {
    st.Push(node);
    node = node->GetDown();
  }
  else if (node->GetLevel() == 3)
    node = st.Get();
}

TTextNode* TTextIter::Get() 
{
  return this->node;
}

TText::TText(char* s)
{
  root = new TTextNode(s, 1);
}

TText::~TText()
{
  TTextNode::FreeMem();
}

TTextIter TText::GetRoot()
{
  return TTextIter(*this, root, TStack<TTextNode*>());
}

TTextIter TText::Find(char c)
{
  TTextIter iter = TTextIter(*this, root, TStack<TTextNode*>());
  while (iter.GoNextChar())
  {
    if (iter.Get()->GetC() == c)
      return iter;
  }
  return iter;
}

TTextIter TText::FindWord(char* c)
{
  TTextIter iter = GetRoot();

  while (iter.GoNext())
  {
    TTextIter result = iter;
    bool word = true;
    int i = 0;
    int n = strlen(c);

    while (iter.GoNext() && i < n)
    {

      if (iter.Get()->GetC() != c[i])
      {
        word = false;
        break;
      }
      i++;
    }

    if (word)
      return result;
  }

  return iter;

}

TTextIter TText::Find(char* s)
{
  TTextIter iter = GetRoot();

  while (iter.GoNextChar())
  {
    TTextIter result = iter;
    bool letter = true;
    bool next = true;
    int n = strlen(s);

    for (int i = 0; i < n; i++)
    {
      if (s[i] != result.Get()->GetC()) {
        letter = false;
        break;
      }
      next = result.GoNextChar();
    }

    if (letter)
      return iter;
  }
}


void TText::Insert(char* c, TTextIter iter)
{
  TTextNode* node = new TTextNode(c, iter.Get()->GetLevel());
  TTextNode* next = iter.Get()->GetNext();
  node->SetNext(next);
  iter.Get()->SetNext(node);
}

void TText::InsertData(char* c, TTextIter iter)
{

  if (iter.Get()->GetNext()->GetC() == ' ' && iter.Get()->GetNext()->GetC() == '.' && iter.Get()->GetNext()->GetC() == '\n')
  {
    iter.GoNext();
    TTextNode* node = new TTextNode(c, 2);
    iter.Get()->SetNext(node);

    int k = strlen(c) + 1;
    for (int i = 0; i < k; i++)
      iter.GoNext();

    node = new TTextNode(" ", 2);
    iter.Get()->SetNext(node);
  }

  else
  {
    TTextNode* next = iter.Get()->GetNext();
    TTextNode* tmp = iter.Get()->GetNext();
    int w = 0;

    while (next->GetC() != ' ' && next->GetC() != '.' && next->GetC() != '\n')
    {
      w++;
      next = next->GetNext();
    }

    char* word = new char[w + 2];
    word[0] = ' ';
    word[w + 2] = NULL;

    for (int i = 1; i < w + 2; i++)
    {
      word[i] = tmp->GetC();
      tmp = tmp->GetNext();
    }

    TTextNode* node = new TTextNode(" ", 2);
    iter.Get()->SetNext(node);

    iter.GoNext();
    iter.GoNext();
    node = new TTextNode(c, 2);
    iter.Get()->SetNext(node);

    int k = strlen(c) + 1;
    for (int i = 0; i < k; i++)
      iter.GoNext();

    node = new TTextNode(word, 2);
    iter.Get()->SetNext(node);
  }
}

void TText::InsertLine(char* c, TTextIter iter)
{
  while (iter.Get()->GetC() != '\n')
    iter.GoNext();

  TTextNode* node = new TTextNode(c, 1);
  iter.Get()->SetNext(node);

  iter.GoNext();
  node = new TTextNode("\n", 2);
  iter.Get()->SetNext(node);
}


void TText::Delete(int count, TTextIter iter)
{
  if (count == 0)
    return;

  TStack<TTextNode*> stack[3];
  int del = 0;
  int level = iter.Get()->GetLevel();

  if (level < 3)
    iter.GoNextChar();

  if (level >= 1 && level <= 3)
  {
    stack[level - 1].Push(iter.Get());
    if (level == 3)
      del++;
  }

  TTextIter it = iter;
  while (it.GoNext() && del < count)
  {
    level = it.Get()->GetLevel();

    if (level >= 1 && level <= 3)
    {
      stack[level - 1].Push(it.Get());

      if (level == 3)
        del++;
    }
  }

  if (del < count)
    throw "Error";

  if (stack[0].IsEmpty() && stack[1].IsEmpty())
  {
    TTextIter prev = iter;
    prev.ResetToWord();
    while (prev.Get()->GetNext() != iter.Get() && prev.Get()->GetDown() != iter.Get())
      prev.GoNext();

    TTextNode* last = stack[2].Get();

    if (prev.Get()->GetLevel() == 2)
      prev.Get()->SetDown(last->GetNext());
    else
      prev.Get()->SetNext(last->GetNext());

    delete last;
    return;
  }


  TTextIter prev = iter;
  prev.ResetToWord();

  while (prev.Get()->GetNext() != iter.Get() && prev.Get()->GetDown() != iter.Get())
    prev.GoNext();

  if (prev.Get()->GetNext() == iter.Get())
    prev.Get()->SetNext(nullptr);

  else
    prev.Get()->SetDown(nullptr);

  if (stack[0].IsEmpty())
  {
    TTextNode* last_word = stack[1].Get();
    TTextNode* last_letter = stack[2].Get();
    TTextIter cur = iter;
    cur.ResetToWord();
    cur.Get()->SetNext(last_word);
    last_word->SetDown(last_letter->GetNext());
    delete last_letter;

    for (int i = 1; i < 3; i++)
    {
      while (!stack[i].IsEmpty())
      {
        TTextNode* del = stack[i].Get();
        delete del;
      }
    }
  }
  else
  {
    TTextNode* last_string = stack[0].Get();
    TTextNode* last_word = stack[1].Get();
    TTextNode* last_letter = stack[2].Get();
    TTextIter cur = iter;
    cur.ResetToString();
    cur.Get()->SetNext(last_string);
    cur.ResetToWord();
    cur.Get()->SetNext(last_word);
    last_word->SetDown(last_letter->GetNext());
    delete last_letter;

    for (int i = 0; i < 3; i++)
    {
      while (!stack[i].IsEmpty())
      {
        TTextNode* temp = stack[i].Get();
        delete temp;
      }
    }
  }
}

char* TText::Copy(int count, TTextIter iter)
{
  if (count < 0)
    throw "Error";

  char* res = new char[count++];

  while (iter.Get()->GetLevel() < 3)
    iter.GoNext();

  if (count > 0)
  {
    res[0] = iter.Get()->GetC();

    for (int i = 0; i < count; i++)
    {
      iter.GoNextChar();
      res[i] = iter.Get()->GetC();
    }
  }

  res[count] = 0;
  return res;
}

std::ostream& operator<<(std::ostream& out, TText& t)
{
  out << *(t.root);
  return out;
}