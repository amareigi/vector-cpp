#include <gtest/gtest.h>

#include <map>

#include "../CONTAINERS/s21_map.h"

TEST(Map, test_create_int) {
  s21::map<int, int> my_map1;

  my_map1.insert(5, 22);
  my_map1.insert(9, 33);
  my_map1.insert(12, 44);
  my_map1.insert(456, 555);

  EXPECT_EQ(my_map1[5], 22);
  EXPECT_EQ(my_map1[9], 33);
  EXPECT_EQ(my_map1[12], 44);
  EXPECT_EQ(my_map1[456], 555);
}
TEST(Map, test_insert1) {
  s21::map<int, int> my_map1;

  std::pair<int, int> w1 = {5, 22};
  std::pair<int, int> w2 = {9, 33};
  std::pair<int, int> w3 = {12, 44};
  std::pair<int, int> w4 = {456, 555};

  my_map1.insert(w1);
  my_map1.insert(w2);
  my_map1.insert(w3);
  my_map1.insert(w4);

  EXPECT_EQ(my_map1[5], 22);
  EXPECT_EQ(my_map1[9], 33);
  EXPECT_EQ(my_map1[12], 44);
  EXPECT_EQ(my_map1[456], 555);
}

TEST(Map, test_insert_or_assign) {
  s21::map<int, int> my_map1{{1, 11}, {2, 22}, {3, 33}};

  my_map1.insert_or_assign(1, 66);
  my_map1.insert_or_assign(4, 44);

  EXPECT_EQ(my_map1[1], 66);
  EXPECT_EQ(my_map1[2], 22);
  EXPECT_EQ(my_map1[3], 33);
  EXPECT_EQ(my_map1[4], 44);
}

TEST(Map, test_create_double) {
  s21::map<double, double> my_map1;

  my_map1.insert(5.5, 2e12);
  my_map1.insert(9.7, 3e-4);
  my_map1.insert(12.1, 44);
  my_map1.insert(456.55, 555);

  EXPECT_EQ(my_map1[5.5], 2e12);
  EXPECT_EQ(my_map1[9.7], 3e-4);
  EXPECT_EQ(my_map1[12.1], 44);
  EXPECT_EQ(my_map1[456.55], 555);
}

TEST(Map, test_create_char) {
  s21::map<int, char> my_map1;

  my_map1.insert(5, '2');
  my_map1.insert(9, '\0');
  my_map1.insert(12, 'e');
  my_map1.insert(456, ' ');

  EXPECT_EQ(my_map1[5], '2');
  EXPECT_EQ(my_map1[9], '\0');
  EXPECT_EQ(my_map1[12], 'e');
  EXPECT_EQ(my_map1[456], ' ');
}

TEST(Map, test_empty) {
  s21::map<int, int> my_map1;
  std::map<int, int> std_map1;

  EXPECT_EQ(my_map1.empty(), std_map1.empty());
}

TEST(Map, test_copy_constructor) {
  s21::map<int, int> my_map1;

  my_map1.insert(5, 50);
  my_map1.insert(9, 12);
  my_map1.insert(12, 44);

  s21::map<int, int> my_map2(my_map1);

  EXPECT_EQ(my_map1[5], my_map2[5]);
  EXPECT_EQ(my_map1[9], my_map2[9]);
  EXPECT_EQ(my_map1[12], my_map2[12]);
}

TEST(Map, test_move_constructor) {
  s21::map<int, int> my_map1;

  my_map1.insert(5, 50);
  my_map1.insert(9, 12);
  my_map1.insert(12, 44);

  s21::map<int, int> my_map2(std::move(my_map1));

  EXPECT_EQ(50, my_map2[5]);
  EXPECT_EQ(12, my_map2[9]);
  EXPECT_EQ(44, my_map2[12]);
  EXPECT_EQ(1, my_map1.empty());
}

TEST(Map, test_init_list_constructor) {
  s21::map<int, int> my_map1{{-4, 222}, {6, 333}, {1, 5676554}, {2, 4}};
  std::map<int, int> std_map1{{-4, 222}, {6, 333}, {1, 5676554}, {2, 4}};

  EXPECT_EQ(my_map1[-4], std_map1[-4]);
  EXPECT_EQ(my_map1[6], std_map1[6]);
  EXPECT_EQ(my_map1[1], std_map1[1]);
  EXPECT_EQ(my_map1[2], std_map1[2]);
}

TEST(Map, test_copy_assign) {
  s21::map<int, int> my_map1;
  s21::map<int, int> my_map2;

  my_map1.insert(5, 50);
  my_map1.insert(9, 12);
  my_map1.insert(12, 44);

  my_map2 = my_map1;

  EXPECT_EQ(my_map1[5], my_map2[5]);
  EXPECT_EQ(my_map1[9], my_map2[9]);
  EXPECT_EQ(my_map1[12], my_map2[12]);
}

TEST(Map, test_move_assign) {
  s21::map<int, int> my_map1;
  s21::map<int, int> my_map2;

  my_map1.insert(5, 50);
  my_map1.insert(9, 12);
  my_map1.insert(12, 44);

  my_map2 = std::move(my_map1);

  EXPECT_EQ(50, my_map2[5]);
  EXPECT_EQ(12, my_map2[9]);
  EXPECT_EQ(44, my_map2[12]);
  EXPECT_EQ(1, my_map1.empty());
}

TEST(Map, test_swap) {
  s21::map<int, int> my_map1{{1, 11}, {2, 22}, {3, 33}};
  s21::map<int, int> my_map2{{-1, -11}, {-2, -22}, {-3, -33}};

  my_map1.swap(my_map2);

  EXPECT_EQ(my_map1[-1], -11);
  EXPECT_EQ(my_map1[-2], -22);
  EXPECT_EQ(my_map1[-3], -33);
  EXPECT_EQ(my_map2[1], 11);
  EXPECT_EQ(my_map2[2], 22);
  EXPECT_EQ(my_map2[3], 33);
}

TEST(Map, iterator_operator) {
  s21::map<int, int> my_map1{{1, 1}, {2, 2}, {3, 3}};

  s21::map<int, int>::iterator my_iter;
  s21::map<int, int>::const_iterator my_c_iter = my_map1.cend();
  int i = 1;
  my_c_iter = my_map1.cbegin();

  for (my_iter = my_map1.begin(); my_iter != my_map1.end(); ++my_iter, ++i) {
    EXPECT_EQ(*my_iter, i);
  }
  my_iter = my_map1.begin();
  s21::map<int, int>::iterator my_iter2 = my_map1.begin();

  EXPECT_EQ(my_iter == my_iter2, 1);
  EXPECT_EQ(my_iter != my_iter2, 0);
}

TEST(Map, test_size) {
  s21::map<int, int> my_map1;

  my_map1.insert(5, 44);
  my_map1.insert(9, 55);
  my_map1.insert(12, 66);
  my_map1.insert(456, 77);

  EXPECT_EQ(my_map1.size(), 4);
}

TEST(Map, test_max_size) {
  s21::map<int, int> my_map1;
  std::map<int, int> std_map1;

  EXPECT_EQ(my_map1.max_size(), std_map1.max_size());
}

TEST(Map, test_clear) {
  s21::map<int, int> my_map1;

  my_map1.insert(5, 44);
  my_map1.insert(9, 55);
  my_map1.insert(12, 66);
  my_map1.insert(456, 77);

  my_map1.clear();

  EXPECT_EQ(my_map1.empty(), 1);
}

TEST(Map, test_erase1) {
  s21::map<int, int> my_map1;
  my_map1.insert(5, 44);

  s21::map<int, int>::iterator my_iter = my_map1.begin();
  my_map1.erase(my_iter);

  EXPECT_EQ(my_map1.empty(), 1);

  my_map1.insert(5, 44);
  my_map1.insert(9, 55);
  my_map1.insert(12, 66);
  my_map1.insert(456, 77);

  my_iter = my_map1.begin();
  my_map1.erase(my_iter);
  my_iter = my_map1.begin();
  EXPECT_EQ(*my_iter, 55);
}

TEST(Map, test_erase2) {
  s21::map<int, int> my_map1;
  my_map1.insert(5, 5);
  my_map1.insert(-4, -4);

  s21::map<int, int>::iterator my_iter;

  my_iter = my_map1.begin();
  ++my_iter;
  my_map1.erase(my_iter);

  EXPECT_EQ(my_map1.size(), 1);
}

TEST(Map, test_merge) {
  s21::map<int, int> my_map1{{1, 11}, {2, 22}, {3, 33}};
  s21::map<int, int> my_map2{{-1, -11}, {-2, -22}, {-3, -33}};

  my_map1.merge(my_map2);

  EXPECT_EQ(my_map1.contains(-1), 1);
  EXPECT_EQ(my_map1.contains(-2), 1);
  EXPECT_EQ(my_map1.contains(-3), 1);
}

TEST(Map, test_contains) {
  s21::map<int, int> my_map1{{1, 11}, {2, 22}, {3, 33}};

  EXPECT_EQ(my_map1.contains(1), 1);
  EXPECT_EQ(my_map1.contains(44), 0);
}

TEST(Map, test_bracket) {
  s21::map<int, int> my_map1{{1, 11}, {2, 22}, {3, 33}};

  EXPECT_EQ(my_map1[1], 11);
  EXPECT_EQ(my_map1[0], 0);
}

TEST(Map, test_at) {
  s21::map<int, int> my_map1{{1, 11}, {2, 22}, {3, 33}};

  EXPECT_EQ(my_map1.at(1), 11);
  EXPECT_ANY_THROW(my_map1.at(55));
}

TEST(Map, test_insert_many) {
  s21::map<int, int> ms{{1, 11}, {2, 22}, {3, 33}};

  s21::map<int, int>::iterator iter = ms.end();

  std::pair<int, int> p1 = {4, 44};
  std::pair<int, int> p2 = {5, 55};
  std::pair<int, int> p3 = {6, 66};
  std::pair<int, int> p4 = {7, 77};

  ms.insert_many(p1, p2, p3, p4);
  --iter;

  EXPECT_EQ(*iter, 77);
  EXPECT_EQ(ms.size(), 7);
}