#include <gtest/gtest.h>

#include <set>

#include "../CONTAINERS/s21_multiset.h"

TEST(Multiset, test_count) {
  s21::multiset<int> my_multiset1;
  std::multiset<int> std_multiset1;

  my_multiset1.insert(5);
  my_multiset1.insert(5);
  my_multiset1.insert(5);
  my_multiset1.insert(9);
  my_multiset1.insert(12);
  my_multiset1.insert(456);

  std_multiset1.insert(5);
  std_multiset1.insert(5);
  std_multiset1.insert(5);
  std_multiset1.insert(9);
  std_multiset1.insert(12);
  std_multiset1.insert(456);

  EXPECT_EQ(my_multiset1.count(5), std_multiset1.count(5));
  EXPECT_EQ(my_multiset1.count(9), std_multiset1.count(9));
}

TEST(Multiset, test_lower_upper) {
  s21::multiset<int> my_multiset1{1, 1, 1, 13, 55, 88};
  std::multiset<int> std_multiset1{1, 1, 1, 13, 55, 88};

  s21::multiset<int>::iterator my_iter = my_multiset1.lower_bound(1);
  std::multiset<int>::iterator std_iter = std_multiset1.lower_bound(1);

  EXPECT_EQ(*my_iter, *std_iter);

  my_iter = my_multiset1.upper_bound(1);
  std_iter = std_multiset1.upper_bound(1);

  EXPECT_EQ(*my_iter, *std_iter);

  my_iter = my_multiset1.upper_bound(14);
  std_iter = std_multiset1.upper_bound(14);

  EXPECT_EQ(*my_iter, *std_iter);

  my_iter = my_multiset1.lower_bound(14);
  std_iter = std_multiset1.lower_bound(14);

  EXPECT_EQ(*my_iter, *std_iter);

  ++my_iter, ++std_iter;
  EXPECT_EQ(*my_iter, *std_iter);

  my_iter = my_multiset1.lower_bound(555);

  EXPECT_EQ(*my_iter, 0);
}

TEST(Multiset, test_clear) {
  s21::multiset<int> my_multiset1;

  my_multiset1.insert(5);
  my_multiset1.insert(9);
  my_multiset1.insert(12);
  my_multiset1.insert(456);

  my_multiset1.clear();

  EXPECT_EQ(my_multiset1.empty(), 1);
}

TEST(Multiset, test_size) {
  s21::multiset<int> my_multiset1;
  std::multiset<int> std_multiset1;

  EXPECT_EQ(my_multiset1.size(), std_multiset1.size());

  my_multiset1.insert(5);
  my_multiset1.insert(9);
  my_multiset1.insert(12);
  my_multiset1.insert(456);

  std_multiset1.insert(5);
  std_multiset1.insert(9);
  std_multiset1.insert(12);
  std_multiset1.insert(456);

  EXPECT_EQ(my_multiset1.size(), std_multiset1.size());
}

TEST(Multiset, test_max_size) {
  s21::multiset<int> my_multiset1;
  std::multiset<int> std_multiset1;

  EXPECT_EQ(my_multiset1.max_size(), std_multiset1.max_size());
}

TEST(Multiset, test_empty) {
  s21::multiset<int> my_set1;
  std::multiset<int> std_set1;

  EXPECT_EQ(my_set1.empty(), std_set1.empty());
}

TEST(Multiset, test_init_list_constructor) {
  s21::multiset<int> my_set1{-4, 6, 5676554, 4};
  std::multiset<int> std_set1{-4, 6, 5676554, 4};

  s21::multiset<int>::iterator my_iter = my_set1.begin();
  std::multiset<int>::iterator std_iter = std_set1.begin();
  EXPECT_EQ(*my_iter, *std_iter);
}

TEST(Multiset, test_copy_assign) {
  s21::multiset<int> my_set1;
  s21::multiset<int> my_set2;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  my_set2 = my_set1;

  s21::multiset<int>::iterator my_iter1 = my_set1.begin();
  s21::multiset<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(*my_iter1, *my_iter2);
}

TEST(Multiset, test_swap) {
  s21::multiset<int> my_set1;
  s21::multiset<int> my_set2;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);
  my_set1.insert(456);

  my_set2.insert(-5);
  my_set2.insert(-9);
  my_set2.insert(-12);
  my_set2.insert(-456);

  my_set1.swap(my_set2);

  s21::multiset<int>::iterator my_iter1 = my_set1.begin();
  s21::multiset<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(*my_iter1, -456);
  EXPECT_EQ(*my_iter2, 5);
}

TEST(Multiset, test_erase) {
  s21::multiset<int> my_set1;
  my_set1.insert(5);

  s21::multiset<int>::iterator my_iter = my_set1.begin();
  my_set1.erase(my_iter);

  EXPECT_EQ(my_set1.empty(), 1);
}

TEST(Multiset, test_merge) {
  s21::multiset<int> my_set1{1, 2, 3};
  s21::multiset<int> my_set2{-5, 14, -3};

  my_set1.merge(my_set2);

  s21::multiset<int>::iterator my_iter1 = my_set1.begin();
  EXPECT_EQ(*my_iter1, -5);
  s21::multiset<int>::const_iterator my_citer = my_set1.cbegin();
  ++my_citer;
  my_citer = my_set2.cend();
}

TEST(Multiset, test_copy_constructor) {
  s21::multiset<int> my_set1;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  s21::multiset<int> my_set2(my_set1);

  s21::multiset<int>::iterator my_iter1 = my_set1.begin();
  s21::multiset<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(*my_iter1, *my_iter2);
}

TEST(Multiset, test_move_constructor) {
  s21::multiset<int> my_set1;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  s21::multiset<int> my_set2(std::move(my_set1));

  s21::multiset<int>::iterator my_iter2 = my_set2.begin();
  EXPECT_EQ(5, *my_iter2);
}

TEST(Multiset, test_move_assign) {
  s21::multiset<int> my_set1;
  s21::multiset<int> my_set2;

  my_set1.insert(5);
  my_set1.insert(9);
  my_set1.insert(12);

  my_set2 = std::move(my_set1);

  s21::multiset<int>::iterator my_iter2 = my_set2.begin();

  EXPECT_EQ(5, *my_iter2);
}

TEST(Multiset, test_insert_many) {
  s21::multiset<int> ms{1, 2, 3};

  s21::multiset<int>::iterator iter = ms.end();

  ms.insert_many(4, 5, 6, 7);
  --iter;

  EXPECT_EQ(*iter, 7);
  EXPECT_EQ(ms.size(), 7);
}