#include <gtest.h>
#include "text.h"
#include "text_node.h"

TEST(TText, can_create_empty_text)
{
  ASSERT_NO_THROW(TText A());
}

TEST(TText, can_create_non_empty_text)
{
  char* const str = "Hello World";
  ASSERT_NO_THROW(TText A(str));
}

TEST(TText, get_the_first_character_of_the_next_word) {
  char* const str = "Hello World";
  TText A(str);
  TTextIter iter = A.GetRoot();

  while (iter.Get()->GetC() != ' ')
    iter.GoNextChar();

  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'W');
}

TEST(TText, can_copy)
{
  char* const str = "Hello World";
  TText A(str);

  char tmp = 'd';
  TTextIter iter = A.Find(tmp);

  ASSERT_NO_THROW(char* res = A.Copy(1, iter));
}

TEST(TText, can_copy_and_get_value)
{
  char* const str = "Hello World";
  TText A(str);

  char tmp = 'W';
  TTextIter iter = A.Find(tmp);
  char* res = A.Copy(1, iter);

  EXPECT_EQ('o', *res);
}

TEST(TTextIter, get_the_first_character) 
{
  char* const str = "Hello World";
  TText A(str);
  TTextIter iter = A.GetRoot();
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'H');
}

TEST(TTextIter, get_the_second_character)
{
  char* const str = "Hello World";
  TText A(str);
  TTextIter iter = A.GetRoot();
  iter.GoNextChar();
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'e');
}

TEST(TTextIter, cannot_get_the_next_character_if_there_is_none) 
{
  char* const str = "A";
  TText A(str);
  TTextIter iter = A.GetRoot();
  iter.GoNextChar();

  ASSERT_EQ(iter.GoNextChar(), false);
}

TEST(TTextIter, can_go_next) 
{
  char* const str = "Hello World";
  TText A(str);
  TTextIter iter = A.GetRoot();
  ASSERT_EQ(iter.GoNext(), true);
}

TEST(TText, can_find_next_char)
{
  char* const str = "Hello World";
  TText A(str);
  TTextIter iter = A.Find('e');
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'l');
}

TEST(TText, can_insert_char)
{
  char* const str = "Hello World";
  TText A(str);
  TTextIter iter = A.GetRoot();
  
  ASSERT_NO_THROW(A.Insert("(o_o)", iter));
}

TEST(TText, can_insert_a_word_in_empty_space)
{
  char* const str = "Hello World";
  TText A(str);
  TTextIter iter = A.GetRoot();
  TTextIter B = A.Find("o");

  ASSERT_NO_THROW(A.InsertData("_", B));
}

TEST(TText, can_insert_a_word_in_word)
{
  char* const str = "Hello World\n   ";
  TText A(str);
  TTextIter iter = A.GetRoot();
  TTextIter B = A.Find("l");

  ASSERT_NO_THROW(A.InsertLine("_", B));
}

TEST(TText, can_find_the_word) 
{
  char* const str = "Hello World";
  TText A(str);

  char* const tmp = "Hello";
  TTextIter iter = A.FindWord(tmp);
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'H');
}

TEST(TText, text_find_word_is_end)
{
  char* const str = "Hello World";
  TText A(str);

  char* const tmp = "HELL";
  TTextIter iter = A.FindWord(tmp);
  ASSERT_EQ(iter.IsEnd(), true);
}

TEST(TText, text_delete)
{
  char* const str = "Hello World";
  TText A(str);

  char* const tmp = "World";
  TTextIter iter = A.FindWord(tmp);
  ASSERT_NO_THROW(A.Delete(1, iter));
}
