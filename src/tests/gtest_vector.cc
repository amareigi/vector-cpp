#include "gtest_start_point.h"

/*----------------------------------------------------------------------------*/
/*------------------------------------main_methods----------------------------*/
/*----------------------------------------------------------------------------*/

TEST(vecMainMethods, default_constructor) {
  s21::vector<int> vec;
  std::vector<int> vec2;
  EXPECT_TRUE(vec.data() == nullptr);
  EXPECT_TRUE(vec.data() == vec2.data());
}

TEST(vecMainMethods, param_constructor) {
  s21::vector<int> vec(10);
  std::vector<int> vec2(10);
  EXPECT_TRUE(vec.size() == vec2.size());
  for (size_t i = 0; i < vec.size(); i++) EXPECT_TRUE(vec[i] == vec2[i]);
}

TEST(vecMainMethods, param_constructor_2) {
  s21::vector<std::vector<int>> vec(1);
  vec.reserve(2);
  std::vector<std::vector<int>> vec2(1);
  vec2.reserve(2);
  EXPECT_TRUE(vec.size() == vec2.size());
  EXPECT_TRUE(vec.capacity() == vec2.capacity());
  for (size_t i = 0; i < vec.size(); i++) EXPECT_TRUE(vec[i] == vec2[i]);
}

TEST(vecMainMethods, param_constructor_3) {
  EXPECT_ANY_THROW(s21::vector<int> vec(-1));
  EXPECT_ANY_THROW(std::vector<int> vec(-1));
}

TEST(vecMainMethods, init_list_constructor) {
  s21::vector<int> vec({1, 2, 3});
  std::vector<int> vec2({1, 2, 3});
  EXPECT_TRUE(vec.size() == vec2.size());
  EXPECT_TRUE(vec.capacity() == vec2.capacity());
  EXPECT_TRUE(vec[0] == vec2[0]);
  EXPECT_TRUE(vec[1] == vec2[1]);
  EXPECT_TRUE(vec[2] == vec2[2]);
}

TEST(vecMainMethods, init_list_constructor_2) {
  s21::vector<std::vector<int>> vec({{1, 2, 3}, {4, 5, 6}});
  std::vector<std::vector<int>> vec2({{1, 2, 3}, {4, 5, 6}});
  EXPECT_TRUE(vec.size() == vec2.size());
  EXPECT_TRUE(vec.capacity() == vec2.capacity());
  EXPECT_TRUE(vec[0][0] == vec2[0][0]);
  EXPECT_TRUE(vec[1][0] == vec2[1][0]);
}

TEST(vecMainMethods, copy_constructor) {
  s21::vector<int> vec_1({1, 2, 3});
  std::vector<int> vec_2({1, 2, 3});
  s21::vector<int> vec_3(vec_1);
  std::vector<int> vec_4(vec_2);
  EXPECT_TRUE(vec_3[0] == vec_4[0]);
  EXPECT_TRUE(vec_3[1] == vec_4[1]);
  EXPECT_TRUE(vec_3[2] == vec_4[2]);
}

TEST(vecMainMethods, copy_constructor_2) {
  s21::vector<int> vec_1;
  std::vector<int> vec_2;

  for (int i = 0; i < 10; i++) {
    vec_1.push_back(i);
    vec_2.push_back(i);
  }

  s21::vector<int> vec_3(vec_1);
  std::vector<int> vec_4(vec_2);

  EXPECT_TRUE(vec_3.size() == vec_4.size());
  EXPECT_TRUE(vec_3.capacity() == vec_4.capacity());

  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(vec_3[i] == vec_4[i]);
  }
}

TEST(vecMainMethods, move_constructor) {
  s21::vector<int> vec_1({1, 2, 3});
  s21::vector<int> vec_2(std::move(vec_1));
  EXPECT_TRUE(vec_1.data() == nullptr);
  EXPECT_TRUE(vec_2.data() != nullptr);
  EXPECT_TRUE(vec_2[0] == 1);
  EXPECT_TRUE(vec_2[1] == 2);
  EXPECT_TRUE(vec_2[2] == 3);
}
TEST(vecMainMethods, move_constructor_2) {
  s21::vector<int> vec_1;
  std::vector<int> vec_2;
  for (int i = 0; i < 10; i++) {
    vec_1.push_back(i);
    vec_2.push_back(i);
  }
  s21::vector<int> vec_3(std::move(vec_1));
  std::vector<int> vec_4(std::move(vec_2));

  EXPECT_TRUE(vec_1.size() == vec_2.size());
  EXPECT_TRUE(vec_1.capacity() == vec_2.capacity());
  EXPECT_TRUE(vec_1.data() == vec_2.data());

  EXPECT_TRUE(vec_3.size() == vec_4.size());
  EXPECT_TRUE(vec_3.capacity() == vec_4.capacity());

  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(vec_3[i] == vec_4[i]);
  }
}
TEST(vecMainMethods, move_constructor_with_allocator) {
  allocator_t<int> Alloc;
  s21::vector<int, allocator_t<int>> vec_1({1, 2, 3}, Alloc);
  s21::vector<int, allocator_t<int>> vec_2(std::move(vec_1), Alloc);
  EXPECT_TRUE(vec_1.data() == nullptr);
  EXPECT_TRUE(vec_2.data() != nullptr);
  EXPECT_TRUE(vec_2[0] == 1);
  EXPECT_TRUE(vec_2[1] == 2);
  EXPECT_TRUE(vec_2[2] == 3);
}

TEST(vecMainMethods, move_constructor_with_allocator_2) {
  allocator_f<int> Alloc;
  s21::vector<int, allocator_f<int>> vec_1({1, 2, 3}, Alloc);
  s21::vector<int, allocator_f<int>> vec_2(std::move(vec_1), Alloc);
  EXPECT_TRUE(vec_1.data() == nullptr);
  EXPECT_TRUE(vec_2.data() != nullptr);
  EXPECT_TRUE(vec_2[0] == 1);
  EXPECT_TRUE(vec_2[1] == 2);
  EXPECT_TRUE(vec_2[2] == 3);
}

TEST(vecMainMethods, copy_assignment) {
  s21::vector<int> vec_1;
  std::vector<int> vec_2;
  for (int i = 0; i < 10; i++) {
    vec_1.push_back(i);
    vec_2.push_back(i);
  }
  s21::vector<int> vec_3;
  std::vector<int> vec_4;

  vec_3 = vec_1;
  vec_4 = vec_2;

  EXPECT_TRUE(vec_1.size() == vec_2.size());
  EXPECT_TRUE(vec_1.capacity() == vec_2.capacity());

  EXPECT_TRUE(vec_3.size() == vec_4.size());
  EXPECT_TRUE(vec_3.capacity() == vec_4.capacity());

  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(vec_3[i] == vec_4[i]);
  }
}

TEST(vecMainMethods, copy_assignment_2) {
  s21::vector<int> vec_1;
  std::vector<int> vec_2;
  for (int i = 0; i < 10; i++) {
    vec_1.push_back(i);
    vec_2.push_back(i);
  }
  s21::vector<int> vec_3(100);
  std::vector<int> vec_4(100);

  vec_3 = vec_1;
  vec_4 = vec_2;

  EXPECT_TRUE(vec_1.size() == vec_2.size());
  EXPECT_TRUE(vec_1.capacity() == vec_2.capacity());

  EXPECT_TRUE(vec_3.size() == vec_4.size());
  EXPECT_TRUE(vec_3.capacity() == vec_4.capacity());

  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(vec_3[i] == vec_4[i]);
  }
}

TEST(vecMainMethods, copy_assignment_3) {
  s21::vector<int> vec_1;
  s21::vector<int> vec_2;
  for (int i = 0; i < 10; i++) {
    vec_1.push_back(i);
    vec_2.push_back(i);
  }

  vec_2 = vec_1 = vec_1;
}

TEST(vecMainMethods, move_assignment) {
  s21::vector<int> vec_1;
  std::vector<int> vec_2;
  for (int i = 0; i < 10; i++) {
    vec_1.push_back(i);
    vec_2.push_back(i);
  }
  s21::vector<int> vec_3(100);
  std::vector<int> vec_4(100);

  vec_3 = std::move(vec_1);
  vec_4 = std::move(vec_2);
  EXPECT_TRUE(vec_1.size() == vec_2.size());
  EXPECT_TRUE(vec_1.capacity() == vec_2.capacity());

  EXPECT_TRUE(vec_3.size() == vec_4.size());
  EXPECT_TRUE(vec_3.capacity() == vec_4.capacity());

  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(vec_3[i] == vec_4[i]);
  }
}

TEST(vecMainMethods, move_assignment_2) {
  s21::vector<int> vec_1;
  std::vector<int> vec_2;
  for (int i = 0; i < 10; i++) {
    vec_1.push_back(i);
    vec_2.push_back(i);
  }
  s21::vector<int> vec_3;
  std::vector<int> vec_4;

  vec_3 = std::move(vec_1);
  vec_4 = std::move(vec_2);
  EXPECT_TRUE(vec_1.size() == vec_2.size());
  EXPECT_TRUE(vec_1.capacity() == vec_2.capacity());

  EXPECT_TRUE(vec_3.size() == vec_4.size());
  EXPECT_TRUE(vec_3.capacity() == vec_4.capacity());

  for (int i = 0; i < 10; i++) EXPECT_TRUE(vec_3[i] == vec_4[i]);
}

TEST(vecMainMethods, move_assignment_with_allocator) {
  allocator_t<int> Alloc;
  s21::vector<int, allocator_t<int>> vec_1({1, 2, 3}, Alloc);
  s21::vector<int, allocator_t<int>> vec_2;
  vec_2 = std::move(vec_1);
  EXPECT_TRUE(vec_1.data() == nullptr);
  EXPECT_TRUE(vec_2.data() != nullptr);
  EXPECT_TRUE(vec_2[0] == 1);
  EXPECT_TRUE(vec_2[1] == 2);
  EXPECT_TRUE(vec_2[2] == 3);
}

 TEST(vecMainMethods, move_assignment_with_allocator_2)
 {

   allocator_f<int> Alloc;
   s21::vector<int, allocator_f<int>> vec_1({1,2,3}, Alloc);
   s21::vector<int, allocator_f<int>> vec_2;
   vec_2 = std::move(vec_1);
   EXPECT_TRUE(vec_1.data() == nullptr);
   EXPECT_TRUE(vec_2.data() != nullptr);
   EXPECT_TRUE(vec_2[0] == 1);
   EXPECT_TRUE(vec_2[1] == 2);
   EXPECT_TRUE(vec_2[2] == 3);

 }

/*----------------------------------------------------------------------------*/
/*-------------------------------modifiers_methods----------------------------*/
/*----------------------------------------------------------------------------*/

TEST(vecModifiers, clear) {
  s21::vector<int> my_vec({1, 2, 3});
  std::vector<int> st_vec({1, 2, 3});
  my_vec.clear();
  st_vec.clear();
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());
}

TEST(vecModifiers, insert) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;

  s21::vector<int>::iterator my_it = my_vec.begin();
  std::vector<int>::iterator st_it = st_vec.begin();

  s21::vector<int>::iterator my_it_new = my_vec.insert(my_it, 1);
  std::vector<int>::iterator st_it_new = st_vec.insert(st_it, 1);

  EXPECT_TRUE(*my_it_new == *st_it_new);
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, insert_2) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
    st_vec.push_back(i);
  }
  s21::vector<int>::iterator my_it = my_vec.end();
  std::vector<int>::iterator st_it = st_vec.end();

  s21::vector<int>::iterator my_it_new = my_vec.insert(my_it, 1);
  std::vector<int>::iterator st_it_new = st_vec.insert(st_it, 1);

  EXPECT_TRUE(*my_it_new == *st_it_new);
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, insert_3) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
    st_vec.push_back(i);
  }
  s21::vector<int>::iterator my_it = my_vec.begin();
  std::vector<int>::iterator st_it = st_vec.begin();

  s21::vector<int>::iterator my_it_new = my_vec.insert(my_it, 1);
  std::vector<int>::iterator st_it_new = st_vec.insert(st_it, 1);

  EXPECT_TRUE(*my_it_new == *st_it_new);
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, erase) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
    st_vec.push_back(i);
  }
  s21::vector<int>::iterator my_it = my_vec.begin();
  std::vector<int>::iterator st_it = st_vec.begin();

  s21::vector<int>::iterator my_it_new = my_vec.erase(my_it);
  std::vector<int>::iterator st_it_new = st_vec.erase(st_it);

  EXPECT_TRUE(*my_it_new == *st_it_new);
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, erase_2) {
  s21::vector<int> my_vec;
  s21::vector<int>::iterator my_it = my_vec.begin();
  EXPECT_NO_THROW(my_vec.erase(my_it));
}

TEST(vecModifiers, erase_3) {
  s21::vector<int> my_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
  }
  s21::vector<int>::iterator my_it = my_vec.end();
  EXPECT_ANY_THROW(my_vec.erase(my_it));
}

TEST(vecModifiers, erase_4) {
  s21::vector<int> my_vec;
  for (int i = 0; i < 5; i++) {
    my_vec.push_back(i);
  }
  for (int i = 0; i < 5; i++) {
    my_vec.push_back(i);
  }
  s21::vector<int>::iterator my_it = my_vec.begin();
  EXPECT_TRUE(my_it == my_vec.begin());
}

TEST(vecModifiers, emplace_back_copy) {
  std::string str1 = "abc";
  std::string str2 = "abc";
  s21::vector<std::string> my_vec;
  std::vector<std::string> st_vec;
  auto& my = my_vec.emplace_back(str1);
  auto& st = st_vec.emplace_back(str2);
  EXPECT_TRUE(str1.size() == str2.size());
  EXPECT_TRUE(my.size() == st.size());
  EXPECT_TRUE(my[0] == st[0]);
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, emplace_back_move) {
  std::string str1 = "abc";
  std::string str2 = "abc";
  s21::vector<std::string> my_vec;
  std::vector<std::string> st_vec;
  auto& my = my_vec.emplace_back(std::move(str1));
  auto& st = st_vec.emplace_back(std::move(str2));
  EXPECT_TRUE(str1.size() == str2.size());
  EXPECT_TRUE(my.size() == st.size());
  EXPECT_TRUE(my[0] == st[0]);
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, push_back) {
  s21::vector<int> my_vec;
  const int tmp = 3;
  for (int i = 0; i < 5; i++) {
    my_vec.push_back(tmp);
  }
}

TEST(vecModifiers, push_back_universal_ref_l_value) {
  std::string my_str = "abc";
  std::string st_str = "abc";
  s21::vector<std::string> my_vec;
  std::vector<std::string> st_vec;
  my_vec.push_back(my_str);
  st_vec.push_back(st_str);
  EXPECT_TRUE(my_str.size() == st_str.size());
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, push_back_universal_ref_r_value) {
  std::string my_str = "abc";
  std::string st_str = "abc";
  s21::vector<std::string> my_vec;
  std::vector<std::string> st_vec;
  my_vec.push_back(std::move(my_str));
  st_vec.push_back(std::move(st_str));
  EXPECT_TRUE(my_str.size() == st_str.size());
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, push_back_const_ref) {
  const std::string my_str = "abc";
  const std::string st_str = "abc";
  s21::vector<std::string> my_vec;
  std::vector<std::string> st_vec;
  my_vec.push_back(my_str);
  st_vec.push_back(st_str);
  EXPECT_TRUE(my_str.size() == st_str.size());
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, pop_back) {
  s21::vector<int> my_vec({1, 2, 3});
  std::vector<int> st_vec({1, 2, 3});
  my_vec.pop_back();
  st_vec.pop_back();
  EXPECT_TRUE(my_vec.size() == st_vec.size());
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

TEST(vecModifiers, pop_back_2) {
  s21::vector<int> my_vec({1});
  my_vec.pop_back();
  my_vec.pop_back();
  my_vec.pop_back();
}

TEST(vecModifiers, swap_alloc_propagate_swap_true) {
  allocator_t<int> Alloc;
  s21::vector<int, allocator_t<int>> my_vec_1({1, 2, 3}, Alloc);
  s21::vector<int, allocator_t<int>> my_vec_2({3, 2, 1}, Alloc);
  my_vec_1.swap(my_vec_2);
}

TEST(vecModifiers, swap_allocs_are_equal) {
  s21::vector<int> my_vec_1({1, 2, 3});
  s21::vector<int> my_vec_2({3, 2, 1});
  std::vector<int> st_vec_1({1, 2, 3});
  std::vector<int> st_vec_2({3, 2, 1});
  my_vec_1.swap(my_vec_2);
  st_vec_1.swap(st_vec_2);
  EXPECT_TRUE(my_vec_1.size() == st_vec_1.size());
  EXPECT_TRUE(my_vec_2.size() == st_vec_2.size());
  for (size_t i = 0; i < st_vec_1.size(); i++)
    EXPECT_TRUE(my_vec_1[i] == st_vec_1[i]);
  for (size_t i = 0; i < st_vec_2.size(); i++)
    EXPECT_TRUE(my_vec_2[i] == st_vec_2[i]);
}

TEST(vecModifiers, swap_allocs_are_not_equal) {
  allocator_f<int> Alloc;
  s21::vector<int, allocator_f<int>> my_vec_1({1, 2, 3}, Alloc);
  s21::vector<int, allocator_f<int>> my_vec_2({3, 2, 1}, Alloc);
  EXPECT_ANY_THROW(my_vec_1.swap(my_vec_2));
}

TEST(vecModifiers, shrink_to_fit) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
    st_vec.push_back(i);
  }
  for (int i = 0; i < 5; i++) {
    my_vec.pop_back();
    st_vec.pop_back();
  }

  my_vec.shrink_to_fit();
  st_vec.shrink_to_fit();

  EXPECT_TRUE(my_vec.size() == st_vec.size());
  EXPECT_TRUE(my_vec.capacity() == st_vec.capacity());

  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec[i] == st_vec[i]);
}

/*----------------------------------------------------------------------------*/
/*-------------------------------element_access_methods-----------------------*/
/*----------------------------------------------------------------------------*/

TEST(vecElemAccess, at) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
    st_vec.push_back(i);
  }
  for (size_t i = 0; i < st_vec.size(); i++)
    EXPECT_TRUE(my_vec.at(i) == st_vec.at(i));
}

TEST(vecElemAccess, at_exception) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  EXPECT_ANY_THROW(my_vec.at(-1));
  EXPECT_ANY_THROW(st_vec.at(-1));
}

TEST(vecElemAccess, front_and_back_and_data) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
    st_vec.push_back(i);
  }
  EXPECT_TRUE(my_vec.front() == st_vec.front());
  EXPECT_TRUE(my_vec.back() == st_vec.back());
  EXPECT_TRUE(*my_vec.data() == *st_vec.data());
}

/*----------------------------------------------------------------------------*/
/*-------------------------------capacity_methods-----------------------------*/
/*----------------------------------------------------------------------------*/

TEST(vecCapacity, empty) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  for (int i = 0; i < 10; i++) {
    my_vec.push_back(i);
    st_vec.push_back(i);
  }
  EXPECT_TRUE(my_vec.empty() == st_vec.empty());
}
TEST(vecCapacity, max_size) {
  s21::vector<int> my_vec;
  std::vector<int> st_vec;
  EXPECT_TRUE(my_vec.max_size() == st_vec.max_size());
}
