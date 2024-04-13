#include <gtest/gtest.h>

#include "../CONTAINERS/s21_array.h"

// Array Member functions

TEST(Array_Member_functions, test_1) {
  s21::array<int, 5> s21_Arr;
  std::array<int, 5> std_Arr = {0};
  int *s21_ptr = s21_Arr.data();
  int *std_ptr = std_Arr.data();
  EXPECT_EQ(std_Arr.size(), s21_Arr.size());
  EXPECT_EQ(s21_ptr, s21_Arr.data());
  EXPECT_EQ(std_ptr, std_Arr.data());
  for (size_t i = 0; i < s21_Arr.size(); ++i) {
    EXPECT_EQ(std_Arr[i], std_Arr[i]);
  }
}

TEST(Array_Member_functions, test_2) {
  s21::array<int, 5> s21_Arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(5, s21_Arr.size());
  for (size_t i = 0; i < s21_Arr.size(); ++i) {
    EXPECT_EQ(i + 1, s21_Arr[i]);
  }
  EXPECT_EQ(std_Arr.size(), s21_Arr.size());
  for (size_t i = 0; i < s21_Arr.size(); ++i) {
    EXPECT_EQ(std_Arr[i], s21_Arr[i]);
  }
}

TEST(Array_Member_functions, test_4) {
  s21::array<int, 5> s21_Arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_Arr2(s21_Arr1);
  EXPECT_EQ(s21_Arr1.size(), s21_Arr2.size());
  for (size_t i = 0; i < s21_Arr1.size(); ++i) {
    EXPECT_EQ(s21_Arr1[i], s21_Arr2[i]);
  }
}

TEST(Array_Member_functions, test_5) {
  s21::array<int, 5> s21_Arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_Arr2 = s21_Arr1;
  EXPECT_EQ(s21_Arr1.size(), s21_Arr2.size());
  for (size_t i = 0; i < s21_Arr1.size(); ++i) {
    EXPECT_EQ(s21_Arr1[i], s21_Arr2[i]);
  }
}

TEST(Array_Member_functions, test_6) {
  s21::array<int, 5> s21_Arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_Arr2(std::move(s21_Arr1));
  EXPECT_EQ(5, s21_Arr2.size());
  for (size_t i = 0; i < s21_Arr2.size(); ++i) {
    EXPECT_EQ(i + 1, s21_Arr2[i]);
  }
  std::array<int, 5> std_Arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr2(std::move(std_Arr1));
  EXPECT_EQ(std_Arr2.size(), s21_Arr2.size());
  for (size_t i = 0; i < s21_Arr1.size(); ++i) {
    EXPECT_EQ(std_Arr2[i], s21_Arr2[i]);
  }
  EXPECT_EQ(std_Arr1.size(), s21_Arr1.size());
  for (size_t i = 0; i < s21_Arr2.size(); ++i) {
    EXPECT_EQ(std_Arr1[i], s21_Arr1[i]);
  }
}

TEST(Array_Member_functions, test_7) {
  s21::array<int, 5> s21_Arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_Arr2 = std::move(s21_Arr1);
  EXPECT_EQ(5, s21_Arr2.size());
  for (size_t i = 0; i < s21_Arr2.size(); ++i) {
    EXPECT_EQ(i + 1, s21_Arr2[i]);
  }
  std::array<int, 5> std_Arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr2 = std::move(std_Arr1);
  EXPECT_EQ(std_Arr2.size(), s21_Arr2.size());
  for (size_t i = 0; i < s21_Arr1.size(); ++i) {
    EXPECT_EQ(std_Arr2[i], s21_Arr2[i]);
  }
  EXPECT_EQ(std_Arr1.size(), s21_Arr1.size());
  for (size_t i = 0; i < s21_Arr2.size(); ++i) {
    EXPECT_EQ(std_Arr1[i], s21_Arr1[i]);
  }
}

// Array Element access

TEST(Array_Element_access, test_1) {
  s21::array<int, 5> s21_Arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < s21_Arr.size(); ++i) {
    EXPECT_EQ(std_Arr.at(i), s21_Arr.at(i));
  }
}

TEST(Array_Element_access, test_2) {
  s21::array<int, 5> s21_Arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < s21_Arr.size(); ++i) {
    EXPECT_EQ(std_Arr[i], s21_Arr[i]);
  }
}

TEST(Array_Element_access, test_3) {
  s21::array<int, 5> s21_Arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(1, s21_Arr.front());
  EXPECT_EQ(std_Arr.front(), s21_Arr.front());
}

TEST(Array_Element_access, test_4) {
  s21::array<int, 5> s21_Arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(5, s21_Arr.back());
  EXPECT_EQ(std_Arr.front(), s21_Arr.front());
}

// Array Iterators

TEST(Array_Iterators, test_1) {
  s21::array<int, 5> s21_Arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(1, *s21_Arr.begin());
  EXPECT_EQ(5, *(s21_Arr.end() - 1));
  EXPECT_EQ(*std_Arr.begin(), *s21_Arr.begin());
  EXPECT_EQ(*(std_Arr.end() - 1), *(s21_Arr.end() - 1));
}

// Array capacity

TEST(Array_capacity, test_1) {
  s21::array<int, 0> s21_Arr;
  std::array<int, 0> std_Arr;
  EXPECT_EQ(std_Arr.empty(), s21_Arr.empty());
  EXPECT_EQ(true, s21_Arr.empty());
}

TEST(Array_capacity, test_2) {
  s21::array<int, 10> s21_Vec;
  std::array<int, 10> std_Vec;
  EXPECT_EQ(std_Vec.size(), s21_Vec.size());
  EXPECT_EQ(10, s21_Vec.size());
}

TEST(Array_capacity, test_3) {
  s21::array<int, 0> s21_Vec;
  std::array<int, 0> std_Vec;
  EXPECT_EQ(std_Vec.size(), s21_Vec.size());
  EXPECT_EQ(0, s21_Vec.size());
}

TEST(Array_capacity, test_4) {
  s21::array<int, 5> s21_Arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(std_Arr.max_size(), s21_Arr.max_size());
}

// Array Modifiers

TEST(Array_Modifiers, test_1) {
  s21::array<int, 5> s21_Arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> s21_Arr2 = {6, 7, 8, 9, 10};
  std::array<int, 5> std_Arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> std_Arr2 = {6, 7, 8, 9, 10};
  s21_Arr1.swap(s21_Arr2);
  std_Arr1.swap(std_Arr2);
  EXPECT_EQ(5, s21_Arr1.size());
  EXPECT_EQ(5, s21_Arr2.size());
  EXPECT_EQ(5, std_Arr1.size());
  EXPECT_EQ(5, std_Arr2.size());
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(i + 6, s21_Arr1[i]);
    EXPECT_EQ(i + 6, std_Arr1[i]);
  }
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(i + 1, s21_Arr2[i]);
    EXPECT_EQ(i + 1, std_Arr2[i]);
  }
}

TEST(Array_Modifiers, test_2) {
  s21::array<int, 5> s21_Arr;
  std::array<int, 5> std_Arr;
  s21_Arr.fill(9);
  std_Arr.fill(9);
  for (size_t i = 0; i < s21_Arr.size(); ++i) {
    EXPECT_EQ(9, s21_Arr[i]);
    EXPECT_EQ(std_Arr[i], s21_Arr[i]);
  }
}

TEST(Array_Modifiers, test_3) {
  s21::array<double, 5> s21_Arr;
  std::array<double, 5> std_Arr;
  s21_Arr.fill(9.5);
  std_Arr.fill(9.5);
  for (size_t i = 0; i < s21_Arr.size(); ++i) {
    EXPECT_EQ(9.5, s21_Arr[i]);
    EXPECT_EQ(std_Arr[i], s21_Arr[i]);
  }
}

class MyClass {
 private:
  std::string name_;

 public:
  MyClass() : name_("") {}
  MyClass(const std::string &name) : name_(name) {}
  std::string getName() const { return name_; }
};

TEST(Array_Modifiers, test_4) {
  s21::array<MyClass, 2> s21_Arr;
  std::array<MyClass, 2> std_Arr;
  MyClass name_1("Anna");
  MyClass name_2("Maria");
  s21_Arr[0] = name_1;
  s21_Arr[1] = name_2;
  std_Arr[0] = name_1;
  std_Arr[1] = name_2;
  EXPECT_EQ("Anna", s21_Arr[0].getName());
  EXPECT_EQ("Maria", s21_Arr[1].getName());
  EXPECT_EQ(std_Arr[0].getName(), s21_Arr[0].getName());
  EXPECT_EQ(std_Arr[1].getName(), s21_Arr[1].getName());
  EXPECT_EQ(std_Arr.size(), s21_Arr.size());
}
