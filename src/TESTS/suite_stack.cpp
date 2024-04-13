#include <gtest/gtest.h>

#include <stack>
#include <vector>

#include "../CONTAINERS/s21_stack.h"

TEST(Stack, test_create_int) {
  s21::stack<int> my_stack1;

  std::stack<int> std_stack1;

  my_stack1.push(5);
  my_stack1.push(9);
  my_stack1.push(12);
  my_stack1.push(456);
  my_stack1.pop();

  std_stack1.push(5);
  std_stack1.push(9);
  std_stack1.push(12);
  std_stack1.push(456);
  std_stack1.pop();

  EXPECT_EQ(my_stack1.top(), std_stack1.top());
  EXPECT_EQ(my_stack1.size(), std_stack1.size());
  EXPECT_EQ(my_stack1.empty(), std_stack1.empty());
}

TEST(Stack, test_create_double) {
  s21::stack<double> my_stack1;

  std::stack<double> std_stack1;

  my_stack1.push(55.67);
  my_stack1.push(-0.4323);
  my_stack1.push(1e23);
  my_stack1.push(4.4);
  my_stack1.pop();

  std_stack1.push(55.67);
  std_stack1.push(-0.4323);
  std_stack1.push(1e23);
  std_stack1.push(4.4);
  std_stack1.pop();

  EXPECT_EQ(my_stack1.top(), std_stack1.top());
  EXPECT_EQ(my_stack1.size(), std_stack1.size());
  EXPECT_EQ(my_stack1.empty(), std_stack1.empty());
}

TEST(Stack, test_create_char) {
  s21::stack<char> my_stack1;

  std::stack<char> std_stack1;

  my_stack1.push('e');
  my_stack1.push('\0');
  my_stack1.push(' ');
  my_stack1.push('\t');
  my_stack1.pop();

  std_stack1.push('e');
  std_stack1.push('\0');
  std_stack1.push(' ');
  std_stack1.push('\t');
  std_stack1.pop();

  EXPECT_EQ(my_stack1.top(), std_stack1.top());
  EXPECT_EQ(my_stack1.size(), std_stack1.size());
  EXPECT_EQ(my_stack1.empty(), std_stack1.empty());
}

TEST(Stack, test_create_container) {
  s21::stack<std::vector<std::string>> my_stack1;

  std::stack<std::vector<std::string>> std_stack1;

  my_stack1.push({"foo", "uiiii"});
  my_stack1.push({"hhhh", "123"});

  std_stack1.push({"foo", "uiiii"});
  std_stack1.push({"hhhh", "123"});

  EXPECT_EQ(my_stack1.top(), std_stack1.top());
  EXPECT_EQ(my_stack1.size(), std_stack1.size());
  EXPECT_EQ(my_stack1.empty(), std_stack1.empty());
}

TEST(Stack, test_empty) {
  s21::stack<int> my_stack1;
  std::stack<int> std_stack1;

  EXPECT_EQ(my_stack1.empty(), std_stack1.empty());
}

TEST(Stack, test_copy_constructor) {
  s21::stack<int> my_stack1;

  my_stack1.push(5);
  my_stack1.push(9);
  my_stack1.push(12);

  s21::stack<int> my_stack2(my_stack1);

  EXPECT_EQ(my_stack1.top(), my_stack2.top());
  EXPECT_EQ(my_stack1.size(), my_stack2.size());
}

TEST(Stack, test_move_constructor) {
  s21::stack<int> my_stack1;

  my_stack1.push(5);
  my_stack1.push(9);
  my_stack1.push(12);

  s21::stack<int> my_stack2(std::move(my_stack1));

  EXPECT_EQ(12, my_stack2.top());
  EXPECT_EQ(3, my_stack2.size());
  EXPECT_EQ(0, my_stack1.size());
}

TEST(Stack, test_init_list_constructor) {
  s21::stack<int> my_stack1;

  my_stack1.push(5);
  my_stack1.push(9);
  my_stack1.push(12);

  s21::stack<int> my_stack2 = {5, 9, 12};

  EXPECT_EQ(my_stack1.top(), my_stack2.top());
  EXPECT_EQ(my_stack1.size(), my_stack2.size());
  EXPECT_EQ(my_stack1.empty(), my_stack2.empty());
}

TEST(Stack, test_copy_assign) {
  s21::stack<int> my_stack1;
  s21::stack<int> my_stack2;

  my_stack1.push(5);
  my_stack1.push(9);
  my_stack1.push(12);
  my_stack2 = my_stack1;

  EXPECT_EQ(my_stack1.top(), my_stack2.top());
  EXPECT_EQ(my_stack1.size(), my_stack2.size());
}

TEST(Stack, test_move_assign) {
  s21::stack<int> my_stack1;
  s21::stack<int> my_stack2;

  my_stack1.push(5);
  my_stack1.push(9);
  my_stack1.push(12);
  my_stack2 = std::move(my_stack1);

  EXPECT_EQ(12, my_stack2.top());
  EXPECT_EQ(3, my_stack2.size());
  EXPECT_EQ(0, my_stack1.size());
}

TEST(Stack, test_swap) {
  s21::stack<int> my_stack1;
  s21::stack<int> my_stack2;

  std::stack<int> std_stack1;
  std::stack<int> std_stack2;

  my_stack1.push(5);
  my_stack1.push(9);
  my_stack1.push(12);

  std_stack1.push(5);
  std_stack1.push(9);
  std_stack1.push(12);

  my_stack1.swap(my_stack2);
  std_stack1.swap(std_stack2);

  EXPECT_EQ(my_stack2.top(), std_stack2.top());
  EXPECT_EQ(my_stack1.empty(), std_stack1.empty());
}

TEST(Stack, test_insert_many) {
  s21::stack<int> ms{1, 2, 3};

  ms.insert_many_front(4, 5, 6, 7);

  EXPECT_EQ(ms.top(), 7);
  EXPECT_EQ(ms.size(), 7);
}