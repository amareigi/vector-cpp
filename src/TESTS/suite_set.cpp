#include <gtest/gtest.h>

#include <set>

#include "../CONTAINERS/s21_set.h"

TEST(Set, test_create_int) {
  s21::set<int> my_set1;
  std::set<int> std_set1;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);
  my_set1.insert(456);

  std_set1.insert(5);
  std_set1.insert(9);
  std_set1.insert(12);
  std_set1.insert(456);

  s21::set<int>::iterator my_iter = my_set1.begin();
  std::set<int>::iterator std_iter = std_set1.begin();
  EXPECT_EQ(*my_iter, *std_iter);
  ++my_iter;
  ++std_iter;
  EXPECT_EQ(*my_iter, *std_iter);
  --my_iter;
  --std_iter;
  EXPECT_EQ(*my_iter, *std_iter);
  --my_iter;
  EXPECT_EQ(*my_iter, 0);
}

TEST(Set, test_create_double) {
  s21::set<double> my_set1;
  std::set<double> std_set1;

  my_set1.insert(5.5);
  my_set1.insert(9.7);
  my_set1.insert(12.44);
  my_set1.insert(456.4);

  std_set1.insert(5.5);
  std_set1.insert(9.7);
  std_set1.insert(12.44);
  std_set1.insert(456.4);

  s21::set<double>::iterator my_iter = my_set1.begin();
  std::set<double>::iterator std_iter = std_set1.begin();
  EXPECT_EQ(*my_iter, *std_iter);
  ++my_iter;
  ++std_iter;
  EXPECT_EQ(*my_iter, *std_iter);
  --my_iter;
  --std_iter;
  EXPECT_EQ(*my_iter, *std_iter);
}

TEST(Set, test_create_char) {
  s21::set<char> my_set1;
  std::set<char> std_set1;

  my_set1.insert('4');
  my_set1.insert('h');
  my_set1.insert('\0');
  my_set1.insert('v');

  std_set1.insert('4');
  std_set1.insert('h');
  std_set1.insert('\0');
  std_set1.insert('v');

  s21::set<char>::iterator my_iter = my_set1.begin();
  std::set<char>::iterator std_iter = std_set1.begin();
  EXPECT_EQ(*my_iter, *std_iter);
}

TEST(Set, test_empty) {
  s21::set<int> my_set1;
  std::set<int> std_set1;

  EXPECT_EQ(my_set1.empty(), std_set1.empty());
}

TEST(Set, test_copy_constructor) {
  s21::set<int> my_set1;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  s21::set<int> my_set2(my_set1);

  s21::set<int>::iterator my_iter1 = my_set1.begin();
  s21::set<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(*my_iter1, *my_iter2);
}

TEST(Set, test_move_constructor) {
  s21::set<int> my_set1;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  s21::set<int> my_set2(std::move(my_set1));

  s21::set<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(5, *my_iter2);
}

TEST(Set, test_init_list_constructor) {
  s21::set<int> my_set1{-4, 6, 5676554, 4};
  std::set<int> std_set1{-4, 6, 5676554, 4};

  s21::set<int>::iterator my_iter = my_set1.begin();
  std::set<int>::iterator std_iter = std_set1.begin();
  EXPECT_EQ(*my_iter, *std_iter);
  ++my_iter;
  ++std_iter;
  EXPECT_EQ(*my_iter, *std_iter);
}

TEST(Set, test_copy_assign) {
  s21::set<int> my_set1;
  s21::set<int> my_set2;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  my_set2 = my_set1;

  s21::set<int>::iterator my_iter1 = my_set1.begin();
  s21::set<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(*my_iter1, *my_iter2);
  ++my_iter1;
  ++my_iter2;
  EXPECT_EQ(*my_iter1, *my_iter2);
}

TEST(Set, test_move_assign) {
  s21::set<int> my_set1;
  s21::set<int> my_set2;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  my_set2 = std::move(my_set1);

  s21::set<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(5, *my_iter2);
  ++my_iter2;
  EXPECT_EQ(9, *my_iter2);
}

TEST(Set, test_swap) {
  s21::set<int> my_set1;
  s21::set<int> my_set2;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);
  my_set1.insert(456);

  my_set2.insert(-5);
  my_set2.insert(-9);
  my_set2.insert(-12);
  my_set2.insert(-456);

  my_set1.swap(my_set2);

  s21::set<int>::iterator my_iter1 = my_set1.begin();
  s21::set<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(*my_iter1, -456);
  EXPECT_EQ(*my_iter2, 5);
  ++my_iter1;
  ++my_iter2;
  EXPECT_EQ(*my_iter1, -12);
  EXPECT_EQ(*my_iter2, 9);
}

TEST(Set, test_iterator_operator) {
  s21::set<int> my_set1;

  my_set1.insert(0);
  my_set1.insert(1);
  my_set1.insert(2);
  my_set1.insert(3);

  s21::set<int>::iterator my_iter;
  int i = 0;

  for (my_iter = my_set1.begin(); my_iter != my_set1.end(); ++my_iter, ++i) {
    EXPECT_EQ(*my_iter, i);
  }
  my_iter = my_set1.begin();
  s21::set<int>::iterator my_iter2 = my_set1.begin();

  EXPECT_EQ(my_iter == my_iter2, 1);
  EXPECT_EQ(my_iter != my_iter2, 0);

  s21::set<int>::const_iterator my_c_iter = my_set1.cbegin();
  i = 0;
  ++my_c_iter;
  --my_c_iter;
  s21::set<int>::const_iterator my_c_iter2 = my_set1.cbegin();

  EXPECT_EQ(my_c_iter == my_c_iter2, 1);
  EXPECT_EQ(my_c_iter != my_c_iter2, 0);
}

TEST(Set, test_size) {
  s21::set<int> my_set1;
  std::set<int> std_set1;

  EXPECT_EQ(my_set1.size(), std_set1.size());

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);
  my_set1.insert(456);

  std_set1.insert(5);
  std_set1.insert(9);
  std_set1.insert(12);
  std_set1.insert(456);

  EXPECT_EQ(my_set1.size(), std_set1.size());
}

TEST(Set, test_max_size) {
  s21::set<int> my_set1;
  std::set<int> std_set1;

  EXPECT_EQ(my_set1.max_size(), std_set1.max_size());
}

TEST(Set, test_clear) {
  s21::set<int> my_set1;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);
  my_set1.insert(456);

  my_set1.clear();

  EXPECT_EQ(my_set1.empty(), 1);
}

TEST(Set, test_erase) {
  s21::set<int> my_set1;
  s21::set<int>::iterator my_iter;
  my_set1.insert(5);

  my_iter = my_set1.begin();
  my_set1.erase(my_iter);

  EXPECT_EQ(my_set1.empty(), 1);

  my_set1.insert(5);
  my_set1.insert(1);
  my_set1.insert(-7);
  my_set1.insert(50);
  my_set1.insert(5000);

  my_iter = my_set1.begin();
  my_set1.erase(my_iter);
  my_iter = my_set1.begin();
  EXPECT_EQ(*my_iter, 1);

  my_iter = my_set1.begin();
  ++my_iter;
  ++my_iter;
  ++my_iter;
  my_set1.erase(my_iter);
  my_iter = my_set1.begin();
  ++my_iter;
  EXPECT_EQ(*my_iter, 5);
}

TEST(Set, test_erase2) {
  s21::set<int> my_set1;
  my_set1.insert(5);
  my_set1.insert(-4);
  my_set1.insert(1);
  my_set1.insert(-7);
  my_set1.insert(88);
  my_set1.insert(-12);
  my_set1.insert(258);
  my_set1.insert(0);
  my_set1.insert(-1);
  my_set1.insert(50);
  my_set1.insert(5000);
  my_set1.insert(125);
  my_set1.insert(-36);
  my_set1.insert(56);
  my_set1.insert(54);
  my_set1.insert(20);
  my_set1.insert(78);
  my_set1.insert(-777);
  my_set1.insert(4532452);
  my_set1.insert(776);

  s21::set<int>::iterator my_iter;

  my_iter = my_set1.begin();
  ++my_iter;
  ++my_iter;
  ++my_iter;
  ++my_iter;
  ++my_iter;
  ++my_iter;
  ++my_iter;
  my_set1.erase(my_iter);
  my_iter = my_set1.begin();
  ++my_iter;
  ++my_iter;
  ++my_iter;
  ++my_iter;
  my_set1.erase(my_iter);
  my_iter = my_set1.begin();
  ++my_iter;
  ++my_iter;
  my_set1.erase(my_iter);
  my_iter = my_set1.begin();
  ++my_iter;
  my_set1.erase(my_iter);
  my_iter = my_set1.begin();
  my_set1.erase(my_iter);
  EXPECT_EQ(my_set1.size(), 15);
  my_iter = my_set1.begin();
  ++my_iter;
  my_set1.erase(my_iter);
  my_iter = my_set1.begin();
  ++my_iter;
  ++my_iter;
  my_set1.erase(my_iter);
}

TEST(Set, test_erase3) {
  s21::set<int> my_set1;
  my_set1.insert(5);
  my_set1.insert(-4);

  s21::set<int>::iterator my_iter;

  my_iter = my_set1.begin();
  ++my_iter;

  my_set1.erase(my_iter);

  EXPECT_EQ(my_set1.size(), 1);
}

TEST(Set, test_merge) {
  s21::set<int> my_set1{1, 2, 3};
  s21::set<int> my_set2{-5, 14, -3};

  my_set1.merge(my_set2);

  s21::set<int>::iterator my_iter1 = my_set1.begin();
  EXPECT_EQ(*my_iter1, -5);
  ++my_iter1;
  EXPECT_EQ(*my_iter1, -3);
  ++my_iter1;
  EXPECT_EQ(*my_iter1, 1);
  s21::set<int>::const_iterator my_citer = my_set1.cbegin();
  ++my_citer;
  my_citer = my_set2.cend();
}

TEST(Set, test_find) {
  s21::set<int> my_set1{1, 2, 3};

  s21::set<int>::iterator my_iter2 = my_set1.find(1);

  s21::set<int>::iterator my_iter1 = my_set1.begin();

  EXPECT_EQ(*my_iter1, *my_iter2);
}

TEST(Set, test_contains) {
  s21::set<int> my_set1{1, 2, 3};

  EXPECT_EQ(my_set1.contains(1), 1);
  EXPECT_EQ(my_set1.contains(44), 0);
}

TEST(Set, test_insert_many) {
  s21::set<int> ms{1, 2, 3};

  s21::set<int>::iterator iter = ms.end();

  ms.insert_many(4, 5, 6, 7);
  --iter;

  EXPECT_EQ(*iter, 7);
  EXPECT_EQ(ms.size(), 7);
}
