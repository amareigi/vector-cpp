#include <gtest/gtest.h>

#include <queue>
#include <vector>

#include "../CONTAINERS/s21_queue.h"

TEST(queue, test_create_int) {
  s21::queue<int> my_queue1;

  std::queue<int> std_queue1;

  my_queue1.push(5);
  my_queue1.push(9);
  my_queue1.push(12);
  my_queue1.push(456);
  my_queue1.pop();

  std_queue1.push(5);
  std_queue1.push(9);
  std_queue1.push(12);
  std_queue1.push(456);
  std_queue1.pop();

  EXPECT_EQ(my_queue1.front(), std_queue1.front());
  EXPECT_EQ(my_queue1.back(), std_queue1.back());
  EXPECT_EQ(my_queue1.size(), std_queue1.size());
  EXPECT_EQ(my_queue1.empty(), std_queue1.empty());
}

TEST(queue, test_create_double) {
  s21::queue<double> my_queue1;

  std::queue<double> std_queue1;

  my_queue1.push(55.67);
  my_queue1.push(-0.4323);
  my_queue1.push(1e23);
  my_queue1.push(4.4);
  my_queue1.pop();

  std_queue1.push(55.67);
  std_queue1.push(-0.4323);
  std_queue1.push(1e23);
  std_queue1.push(4.4);
  std_queue1.pop();

  EXPECT_EQ(my_queue1.front(), std_queue1.front());
  EXPECT_EQ(my_queue1.back(), std_queue1.back());
  EXPECT_EQ(my_queue1.size(), std_queue1.size());
  EXPECT_EQ(my_queue1.empty(), std_queue1.empty());
}

TEST(queue, test_create_char) {
  s21::queue<char> my_queue1;

  std::queue<char> std_queue1;

  my_queue1.push('e');
  my_queue1.push('\0');
  my_queue1.push(' ');
  my_queue1.push('\t');
  my_queue1.pop();

  std_queue1.push('e');
  std_queue1.push('\0');
  std_queue1.push(' ');
  std_queue1.push('\t');
  std_queue1.pop();

  EXPECT_EQ(my_queue1.front(), std_queue1.front());
  EXPECT_EQ(my_queue1.back(), std_queue1.back());
  EXPECT_EQ(my_queue1.size(), std_queue1.size());
  EXPECT_EQ(my_queue1.empty(), std_queue1.empty());
}

TEST(queue, test_create_container) {
  s21::queue<std::vector<std::string>> my_queue1;

  std::queue<std::vector<std::string>> std_queue1;

  my_queue1.push({"foo", "uiiii"});
  my_queue1.push({"hhhh", "123"});

  std_queue1.push({"foo", "uiiii"});
  std_queue1.push({"hhhh", "123"});

  EXPECT_EQ(my_queue1.front(), std_queue1.front());
  EXPECT_EQ(my_queue1.back(), std_queue1.back());
  EXPECT_EQ(my_queue1.size(), std_queue1.size());
  EXPECT_EQ(my_queue1.empty(), std_queue1.empty());
}

TEST(queue, test_empty) {
  s21::queue<int> my_queue1;
  std::queue<int> std_queue1;

  EXPECT_EQ(my_queue1.empty(), std_queue1.empty());
}

TEST(queue, test_copy_constructor) {
  s21::queue<int> my_queue1;

  my_queue1.push(5);
  my_queue1.push(9);
  my_queue1.push(12);

  s21::queue<int> my_queue2(my_queue1);

  EXPECT_EQ(my_queue1.front(), my_queue2.front());
  EXPECT_EQ(my_queue1.back(), my_queue2.back());
  EXPECT_EQ(my_queue1.size(), my_queue2.size());
}

TEST(queue, test_move_constructor) {
  s21::queue<int> my_queue1;

  my_queue1.push(5);
  my_queue1.push(9);
  my_queue1.push(12);

  s21::queue<int> my_queue2(std::move(my_queue1));

  EXPECT_EQ(5, my_queue2.front());
  EXPECT_EQ(12, my_queue2.back());
  EXPECT_EQ(3, my_queue2.size());
  EXPECT_EQ(0, my_queue1.size());
}

TEST(queue, test_init_list_constructor) {
  s21::queue<int> my_queue1;

  my_queue1.push(5);
  my_queue1.push(9);
  my_queue1.push(12);

  s21::queue<int> my_queue2 = {5, 9, 12};

  EXPECT_EQ(my_queue1.front(), my_queue2.front());
  EXPECT_EQ(my_queue1.back(), my_queue2.back());
  EXPECT_EQ(my_queue1.size(), my_queue2.size());
  EXPECT_EQ(my_queue1.empty(), my_queue2.empty());
}

TEST(queue, test_copy_assign) {
  s21::queue<int> my_queue1;
  s21::queue<int> my_queue2;

  my_queue1.push(5);
  my_queue1.push(9);
  my_queue1.push(12);
  my_queue2 = my_queue1;

  EXPECT_EQ(my_queue1.front(), my_queue2.front());
  EXPECT_EQ(my_queue1.back(), my_queue2.back());
  EXPECT_EQ(my_queue1.size(), my_queue2.size());
}

TEST(queue, test_move_assign) {
  s21::queue<int> my_queue1;
  s21::queue<int> my_queue2;

  my_queue1.push(5);
  my_queue1.push(9);
  my_queue1.push(12);
  my_queue2 = std::move(my_queue1);

  EXPECT_EQ(5, my_queue2.front());
  EXPECT_EQ(12, my_queue2.back());
  EXPECT_EQ(3, my_queue2.size());
  EXPECT_EQ(0, my_queue1.size());
}

TEST(queue, test_swap) {
  s21::queue<int> my_queue1;
  s21::queue<int> my_queue2;

  std::queue<int> std_queue1;
  std::queue<int> std_queue2;

  my_queue1.push(5);
  my_queue1.push(9);
  my_queue1.push(12);

  std_queue1.push(5);
  std_queue1.push(9);
  std_queue1.push(12);

  my_queue1.swap(my_queue2);
  std_queue1.swap(std_queue2);

  EXPECT_EQ(my_queue2.front(), std_queue2.front());
  EXPECT_EQ(my_queue2.back(), std_queue2.back());
  EXPECT_EQ(my_queue1.empty(), std_queue1.empty());
}

TEST(queue, test_insert_many) {
  s21::queue<int> ms{1, 2, 3};

  ms.insert_many_back(4, 5, 6, 7);

  EXPECT_EQ(ms.back(), 7);
  EXPECT_EQ(ms.front(), 1);
  EXPECT_EQ(ms.size(), 7);
}
