#include <gtest/gtest.h>

#include "s21_containers.h"
#include "s21_containersplus.h"

#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

// Vector
class VectorTest : public ::testing::Test {
public:
  s21::vector<int> int_vector = {1, 2, 3, 4, 5, 6};
  s21::vector<int> const const_vector = {1, 2, 3, 4, 5, 6};
  s21::vector<float> float_vector = {1.342, 2.123, 3.978, 4.43, 5.3, 0};
  s21::vector<double> double_vector = {4.34, 42.1123, 23.123, 6.43, 5.31, 0.02};
  s21::vector<char> char_vector = {'a', 'b', 'c', 'd'};
  s21::vector<std::string> string_vector = {"one", "two", "three"};
  s21::vector<int> empty_vector;

  std::vector<int> int_vector_std = {1, 2, 3, 4, 5, 6};
  std::vector<int> const const_vector_std = {1, 2, 3, 4, 5, 6};
  std::vector<float> float_vector_std = {1.342, 2.123, 3.978, 4.43, 5.3, 0};
  std::vector<double> double_vector_std = {4.34, 42.1123, 23.123,
                                           6.43, 5.31,    0.02};
  std::vector<char> char_vector_std = {'a', 'b', 'c', 'd'};
  std::vector<std::string> string_vector_std = {"one", "two", "three"};
  std::vector<int> empty_vector_std;
};

TEST_F(VectorTest, TestAt) {
  int_vector.at(4) = 256;
  int_vector_std.at(4) = 256;
  ASSERT_EQ(int_vector.at(4), int_vector_std.at(4));
}

TEST_F(VectorTest, TestAtConst) {
  ASSERT_EQ(const_vector.at(4), const_vector_std.at(4));
}

TEST_F(VectorTest, TestReferenceOperator) {
  int_vector[3] = 123;
  int_vector_std[3] = 123;
  ASSERT_EQ(int_vector[3], int_vector_std[3]);
}

TEST_F(VectorTest, TestReferenceOperatorConst) {
  ASSERT_EQ(const_vector[3], const_vector_std[3]);
}

TEST_F(VectorTest, TestFront) {
  ASSERT_EQ(float_vector.front(), float_vector_std.front());
}

TEST_F(VectorTest, TestBack) {
  ASSERT_EQ(float_vector.back(), float_vector_std.back());
}

TEST_F(VectorTest, TestData) {
  s21::vector<int>::iterator it;
  it = int_vector.begin();
  std::vector<int>::iterator it_std;
  it_std = int_vector_std.begin();
  ASSERT_EQ(it[3], it_std[3]);
}

TEST_F(VectorTest, TestBegin) {
  s21::vector<int>::iterator it;
  it = int_vector.begin();
  std::vector<int>::iterator it_std;
  it_std = int_vector_std.begin();
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestBeginConst) {
  s21::vector<int>::const_iterator it;
  it = const_vector.begin();
  std::vector<int>::const_iterator it_std;
  it_std = const_vector_std.begin();
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestEnd) {
  s21::vector<int>::iterator it;
  it = int_vector.end() - 1;
  std::vector<int>::iterator it_std;
  it_std = int_vector_std.end() - 1;
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestEndConst) {
  s21::vector<int>::const_iterator it;
  it = const_vector.end() - 1;
  std::vector<int>::const_iterator it_std;
  it_std = const_vector_std.end() - 1;
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestEmpty) { ASSERT_TRUE(empty_vector.empty()); }
TEST_F(VectorTest, TestEmpty2) { ASSERT_FALSE(string_vector.empty()); }
TEST_F(VectorTest, TestEmptyConst) { ASSERT_FALSE(const_vector.empty()); }
TEST_F(VectorTest, TestSize) {
  ASSERT_EQ(string_vector_std.size(), string_vector.size());
}
TEST_F(VectorTest, TestMaxSize) {
  ASSERT_EQ(string_vector_std.max_size(), string_vector.max_size());
}
TEST_F(VectorTest, TestReserve) {
  double_vector.reserve(14);
  double_vector_std.reserve(14);
  ASSERT_EQ(double_vector.size(), double_vector_std.size());
  ASSERT_EQ(double_vector.capacity(), double_vector_std.capacity());
}
TEST_F(VectorTest, TestCapacity) {
  ASSERT_EQ(string_vector_std.capacity(), string_vector.capacity());
}
TEST_F(VectorTest, TestShrinkToFit) {
  double_vector.reserve(20);
  double_vector_std.reserve(20);
  double_vector.shrink_to_fit();
  double_vector_std.shrink_to_fit();
  ASSERT_EQ(double_vector.size(), double_vector_std.size());
  ASSERT_EQ(double_vector.capacity(), double_vector_std.capacity());
}

TEST_F(VectorTest, TestClear) {
  double_vector.clear();
  double_vector_std.clear();
  ASSERT_EQ(double_vector.size(), double_vector_std.size());
  ASSERT_EQ(double_vector.capacity(), double_vector_std.capacity());
}

TEST_F(VectorTest, TestInsert) {
  char_vector.insert(char_vector.end(), 't');
  char_vector_std.insert(char_vector_std.end(), 't');
  ASSERT_EQ(char_vector_std.back(), char_vector_std.back());
  ASSERT_EQ(char_vector_std.size(), char_vector_std.size());
  ASSERT_EQ(char_vector_std.capacity(), char_vector_std.capacity());
}

TEST_F(VectorTest, TestInsert2) {
  int_vector.insert(int_vector.begin() + 1, 444);
  int_vector_std.insert(int_vector_std.begin() + 1, 444);
  s21::vector<int>::iterator it = int_vector.begin();
  std::vector<int>::iterator it_std = int_vector_std.begin();
  while (it != int_vector.end() || it_std != int_vector_std.end()) {
    ASSERT_EQ(*it, *it_std);
    ++it;
    ++it_std;
  }
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestErase) {
  char_vector.erase(char_vector.end() - 1);
  char_vector_std.erase(char_vector_std.end() - 1);
  ASSERT_EQ(char_vector_std.back(), char_vector_std.back());
  ASSERT_EQ(char_vector_std.size(), char_vector_std.size());
  ASSERT_EQ(char_vector_std.capacity(), char_vector_std.capacity());
}

TEST_F(VectorTest, TestErase2) {
  int_vector.erase(int_vector.begin() + 1);
  int_vector_std.erase(int_vector_std.begin() + 1);
  s21::vector<int>::iterator it = int_vector.begin();
  std::vector<int>::iterator it_std = int_vector_std.begin();
  while (it != int_vector.end() || it_std != int_vector_std.end()) {
    ASSERT_EQ(*it, *it_std);
    ++it;
    ++it_std;
  }
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestPushBack) {
  int_vector.push_back(481223);
  int_vector_std.push_back(481223);
  ASSERT_EQ(int_vector.back(), int_vector_std.back());
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestPushBack2) {
  int_vector.reserve(20);
  int_vector_std.reserve(20);
  int_vector.push_back(20);
  int_vector_std.push_back(20);
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
  ASSERT_EQ(int_vector.back(), int_vector_std.back());
}

TEST_F(VectorTest, TestPopBack) {
  int_vector.pop_back();
  int_vector_std.pop_back();
  ASSERT_EQ(int_vector.back(), int_vector_std.back());
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestSwap) {
  int_vector.swap(empty_vector);
  int_vector_std.swap(empty_vector_std);
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
  ASSERT_EQ(empty_vector.size(), empty_vector_std.size());
  ASSERT_EQ(empty_vector.capacity(), empty_vector_std.capacity());
  while (!empty_vector.empty() && !empty_vector_std.empty()) {
    ASSERT_EQ(empty_vector.back(), empty_vector_std.back());
    empty_vector.pop_back();
    empty_vector_std.pop_back();
  }
  ASSERT_EQ(int_vector.empty(), int_vector_std.empty());
  ASSERT_TRUE(int_vector.empty());
}

TEST_F(VectorTest, TestInsertMany) {
  int_vector.insert_many(int_vector.begin() + 1, 162342);
  int_vector_std.emplace(int_vector_std.begin() + 1, 162342);
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
  while (!int_vector.empty() && !int_vector_std.empty()) {
    ASSERT_EQ(int_vector.back(), int_vector_std.back());
    int_vector.pop_back();
    int_vector_std.pop_back();
  }
}

TEST_F(VectorTest, TestInsertMany2) {
  int_vector.insert_many(int_vector.begin() + 1, 4234, 23423, 234234, 432,
                         2423423, 234242, 4234234, 4234234, 4324234, 42342342,
                         2342342, 234234, 234234, 234, 23, 2, 11);
  s21::vector<int> result{1,      4234,    23423,   234234,  432,      2423423,
                          234242, 4234234, 4234234, 4324234, 42342342, 2342342,
                          234234, 234234,  234,     23,      2,        11,
                          2,      3,       4,       5,       6};
  s21::vector<int>::iterator it = int_vector.begin();
  s21::vector<int>::iterator it_res = result.begin();
  while (it != int_vector.end() || it_res != result.end()) {
    ASSERT_EQ(*it, *it_res);
    ++it;
    ++it_res;
  }
}

TEST_F(VectorTest, TestInsertManyBack) {
  int_vector.insert_many_back(162342);
  int_vector_std.emplace_back(162342);
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
  while (!int_vector.empty() && !int_vector_std.empty()) {
    ASSERT_EQ(int_vector.back(), int_vector_std.back());
    int_vector.pop_back();
    int_vector_std.pop_back();
  }
}

TEST_F(VectorTest, TestInsertManyBack2) {
  int_vector.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8);
  for (int i = 1; i <= 8; i++) {
    int_vector_std.push_back(i);
  }
  ASSERT_EQ(int_vector.size(), int_vector_std.size());
  ASSERT_EQ(int_vector.capacity(), int_vector_std.capacity());
  while (!int_vector.empty() && !int_vector_std.empty()) {
    ASSERT_EQ(int_vector.back(), int_vector_std.back());
    int_vector.pop_back();
    int_vector_std.pop_back();
  }
}

// Stack

class StackTest : public ::testing::Test {
public:
  s21::stack<int> empty_stack;
  std::stack<int> empty_stack_original;
  s21::stack<int> *int_stack;
  std::stack<int> *int_stack_original;
  s21::stack<int> *my_stack;
  std::stack<int> *original_stack;
  void SetUp() override {
    int_stack = new s21::stack<int>;
    int_stack_original = new std::stack<int>;
    int_stack->push(324);
    int_stack->push(768678);
    int_stack->push(54342);
    int_stack->push(6563);
    int_stack_original->push(324);
    int_stack_original->push(768678);
    int_stack_original->push(54342);
    int_stack_original->push(6563);
    my_stack = new s21::stack<int>;
    original_stack = new std::stack<int>;
    for (int i = 0; i <= 5; i++) {
      my_stack->push(i);
      original_stack->push(i);
    }
  }
  void TearDown() override {
    delete int_stack;
    delete int_stack_original;
    delete my_stack;
    delete original_stack;
  }
};

TEST_F(StackTest, TestDefaultConstructor) {
  ASSERT_EQ(empty_stack.size(), empty_stack_original.size());
}

TEST_F(StackTest, TestCopyConstructor) {
  s21::stack<int> my_stack_copy(*my_stack);
  std::stack<int> original_stack_copy(*original_stack);
  while (!my_stack_copy.empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.top(), original_stack_copy.top());
    my_stack_copy.pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestMoveConstructor) {
  s21::stack<int> my_stack_copy(std::move(*my_stack));
  std::stack<int> original_stack_copy(std::move(*original_stack));
  while (!my_stack_copy.empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.top(), original_stack_copy.top());
    my_stack_copy.pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestCopyOperator) {
  s21::stack<int> my_stack_copy = *my_stack;
  std::stack<int> original_stack_copy = *original_stack;
  while (!my_stack_copy.empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.top(), original_stack_copy.top());
    my_stack_copy.pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestMoveOperator) {
  s21::stack<int> my_stack_copy = std::move(*my_stack);
  std::stack<int> original_stack_copy = std::move(*original_stack);
  while (!my_stack_copy.empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.top(), original_stack_copy.top());
    my_stack_copy.pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestTop) {
  ASSERT_EQ(my_stack->top(), original_stack->top());
}

TEST_F(StackTest, TestSize) {
  ASSERT_EQ(my_stack->size(), original_stack->size());
}

TEST_F(StackTest, TestSwap) {
  int_stack->swap(empty_stack);
  int_stack_original->swap(empty_stack_original);
  while (!int_stack->empty() && !int_stack_original->empty()) {
    ASSERT_EQ(int_stack->top(), int_stack_original->top());
    int_stack->pop();
    int_stack_original->pop();
  }
  ASSERT_EQ(int_stack->empty(), int_stack_original->empty());
}

TEST_F(StackTest, TestEmplaceFront) {
  int_stack->insert_many_front(481223);
  int_stack_original->emplace(481223);
  while (!int_stack->empty() && !int_stack_original->empty()) {
    ASSERT_EQ(int_stack->top(), int_stack_original->top());
    int_stack->pop();
    int_stack_original->pop();
  }
  ASSERT_EQ(int_stack->empty(), int_stack_original->empty());
}

// Queue

class TestQueue : public ::testing::Test {
public:
  s21::queue<int> empty_queue;
  std::queue<int> empty_queue_original;
  std::deque<int> numbers = {1, 2, 3, 4, 5};
  std::queue<int> std_queue{numbers};
  s21::queue<int> s21_queue = {1, 2, 3, 4, 5};
  std::queue<int> queue_1;
  s21::queue<int> queue_2;
  std::deque<std::string> str = {"I Love School"};
  std::queue<std::string> queue_str1{str};
  s21::queue<std::string> queue_str2 = {"I Love School"};
  std::deque<std::string> string_deque = {"School S21", " in ", "Kazan"};
  std::queue<std::string> std_queue_str{string_deque};
  s21::queue<std::string> s21_queue_str = {"School S21", " in ", "Kazan"};
  std::deque<std::string> string_deque_2 = {"I ", "from ", "Dagestan"};
  std::queue<std::string> std_queue_2{string_deque_2};
  s21::queue<std::string> s21_queue_str_2 = {"I ", "from ", "Dagestan"};
};

TEST_F(TestQueue, Constructor_Default) {
  EXPECT_EQ(empty_queue.empty(), empty_queue_original.empty());
  EXPECT_EQ(empty_queue.size(), empty_queue_original.size());
}

TEST_F(TestQueue, Constructor_Init) {
  while (!s21_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    s21_queue.pop();
    std_queue.pop();
  }
}

TEST_F(TestQueue, Constructor_Copy) {
  std::queue<int> std_queue_2(std_queue);
  std::queue<int> std_queue_3;
  std_queue_3 = std_queue_2;

  s21::queue<int> s21_queue_2(s21_queue);
  s21::queue<int> s21_queue_3;
  s21_queue_3 = s21_queue_2;

  EXPECT_EQ(std_queue.size(), s21_queue.size());
  EXPECT_EQ(std_queue_2.size(), std_queue_2.size());
  EXPECT_EQ(std_queue_3.size(), s21_queue_3.size());
  while (!s21_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    EXPECT_EQ(s21_queue_2.front(), std_queue_2.front());
    EXPECT_EQ(s21_queue_3.front(), std_queue_3.front());
    s21_queue.pop();
    std_queue.pop();
    s21_queue_2.pop();
    std_queue_2.pop();
    s21_queue_3.pop();
    std_queue_3.pop();
  }
}

TEST_F(TestQueue, Constructor_Move) {
  std::queue<int> std_queue_2(std::move(std_queue));
  s21::queue<int> s21_queue_2(std::move(s21_queue));
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
  while (!s21_queue_2.empty()) {
    EXPECT_EQ(s21_queue_2.front(), std_queue_2.front());
    s21_queue_2.pop();
    std_queue_2.pop();
  }

  std::queue<int> std_queue_3{numbers};
  std_queue_2 = std::move(std_queue_3);

  s21::queue<int> s21_queue_3{1, 2, 3};
  s21_queue_2 = std::move(s21_queue_3);

  EXPECT_EQ(s21_queue_3.empty(), std_queue_3.empty());
  while (!s21_queue_2.empty()) {
    EXPECT_EQ(s21_queue_2.front(), std_queue_2.front());
    s21_queue_2.pop();
    std_queue_2.pop();
  }
}

TEST_F(TestQueue, Test_Push) {
  for (int i = 0; i < 5; ++i) {
    queue_1.push(i);
    queue_2.push(i);
    EXPECT_EQ(queue_1.size(), queue_2.size());
    EXPECT_EQ(queue_1.back(), queue_2.back());
  }
}

TEST_F(TestQueue, Test_Push_2) {
  queue_str1.push(" S21");
  queue_str2.push(" S21");
  EXPECT_EQ(queue_str1.size(), queue_str2.size());
  while (!queue_2.empty()) {
    EXPECT_EQ(queue_str1.front(), queue_str2.front());
    queue_str1.pop();
    queue_str2.pop();
  }
}

TEST_F(TestQueue, Test_Swap) {
  std_queue_str.swap(std_queue_2);
  s21_queue_str.swap(s21_queue_str_2);
  while (!std_queue_str.empty()) {
    EXPECT_EQ(s21_queue_str.front(), std_queue_str.front());
    s21_queue_str.pop();
    std_queue_str.pop();
  }
  while (!std_queue_2.empty()) {
    EXPECT_EQ(s21_queue_str_2.front(), std_queue_2.front());
    s21_queue_str_2.pop();
    std_queue_2.pop();
  }
}

TEST_F(TestQueue, Test_InsertManyBack) {
  for (int i = 6; i < 8; ++i) {
    std_queue.push(i);
  }
  s21_queue.insert_many_back(6, 7, 8);
  while (!std_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    s21_queue.pop();
    std_queue.pop();
  }
}

// List

class TestList : public ::testing::Test {
public:
  std::list<int> empty_list_std;
  s21::list<int> empty_list_s21;
  std::list<int> list_std{1, 2, 3};
  std::list<int> list_std_2{5, 6, 7};
  s21::list<int> list_s21{1, 2, 3};
  s21::list<int> list_s21_2{5, 6, 7};
  std::list<int> list_std_3 = {5, 0, 2};
  s21::list<int> list_s21_3 = {5, 0, 2};
  std::list<int> list_std_4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> list_s21_4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<std::string> list_str_std = {"I Love School"};
  s21::list<std::string> list_str_s21 = {"I Love School"};
  std::list<char> list_char_std = {'D', 'A', 'G'};
  s21::list<char> list_char_s21 = {'D', 'A', 'G'};
  std::list<char> list_char_std_2 = {'a', 'b', 'b', 'a', 'c', 'x',
                                     'y', 'y', 'y', 'z', 'z'};
  s21::list<char> list_char_s21_2 = {'a', 'b', 'b', 'a', 'c', 'x',
                                     'y', 'y', 'y', 'z', 'z'};
  std::list<char> list_char_std_3 = {'y', 'c', 'z', 'a', 'a', 'x',
                                     'w', 'v', 't', 'e', 'q'};
  s21::list<char> list_char_s21_3 = {'y', 'c', 'z', 'a', 'a', 'x',
                                     'w', 'v', 't', 'e', 'q'};
  std::list<std::string> std_kazan = {"I study ", " in Kazan"};
  std::list<std::string> std_school = {" at school ", "s21"};
  s21::list<std::string> s21_kazan = {"I study ", " in Kazan"};
  s21::list<std::string> s21_school = {" at school ", "s21"};
};

TEST_F(TestList, Constructor_Default) {
  EXPECT_EQ(empty_list_std.empty(), empty_list_s21.empty());
  EXPECT_EQ(empty_list_std.size(), empty_list_s21.size());
}

TEST_F(TestList, Constructor_Size) {
  size_t count = 4;
  std::list<int> list_1(count);
  s21::list<int> list_2(count);
  EXPECT_EQ(list_1.size(), list_2.size());
}

TEST_F(TestList, Constructor_Init) {
  auto iter_2 = list_s21.begin();
  for (auto i = list_std.begin(); i != list_std.end(); ++i, ++iter_2) {
    EXPECT_EQ(*i, *iter_2);
  }
}

TEST_F(TestList, Constructor_Copy) {
  std::list<int> list_1(list_std);
  list_std_2 = list_1;
  s21::list<int> list_2(list_s21);
  list_s21_2 = list_2;

  EXPECT_EQ(list_1.size(), list_2.size());
  EXPECT_EQ(list_std_2.size(), list_s21_2.size());
  EXPECT_EQ(list_std.size(), list_s21.size());
  auto it = list_2.begin();
  auto it2 = list_std_2.begin();
  for (auto i = list_1.begin(); i != list_1.begin(); ++i, ++it) {
    EXPECT_EQ(*i, *it);
  }
  for (auto i = list_std_2.begin(); i != list_std_2.begin(); ++i, ++it2) {
    EXPECT_EQ(*i, *it2);
  }
}

TEST_F(TestList, Constructor_Move) {
  std::list<int> list_1(std::move(list_std));
  s21::list<int> list_2(std::move(list_s21));
  EXPECT_EQ(list_1.size(), list_2.size());
  EXPECT_EQ(list_std.size(), list_s21.size());
  auto it = list_2.begin();
  for (auto i = list_1.begin(); i != list_1.begin(); ++i, ++it) {
    EXPECT_EQ(*i, *it);
  }
  list_std_2 = std::move(list_1);
  s21::list<int> list_s21_2{5, 6, 7};
  list_s21_2 = std::move(list_2);
  EXPECT_EQ(list_1.size(), list_2.size());
  EXPECT_EQ(list_std_2.size(), list_s21_2.size());
  auto it2 = list_s21_2.begin();
  for (auto i = list_std_2.begin(); i != list_std_2.begin(); ++i, ++it) {
    EXPECT_EQ(*i, *it2);
  }
}

TEST_F(TestList, Test_PushFront) {
  std::list<int> list1;
  s21::list<int> list2;
  auto it = list1.begin();
  auto it2 = list2.begin();
  for (int i = 0; i < 5; ++i, ++it, ++it2) {
    list1.push_front(i);
    list2.push_front(i);
    EXPECT_EQ(list1.size(), list2.size());
    EXPECT_EQ(*it, *it2);
  }
}

TEST_F(TestList, Test_PushBack) {
  list_str_std.push_back(" S21");
  list_str_s21.push_back(" S21");
  EXPECT_EQ(list_str_std.size(), list_str_s21.size());
  auto it = list_str_std.begin();
  for (auto i = list_str_std.begin(); i != list_str_std.end(); ++i, ++it) {
    EXPECT_EQ(*it, *i);
  }
}

TEST_F(TestList, Test_PopFront) {
  auto it = list_std.begin();
  auto it2 = list_s21.begin();
  EXPECT_EQ(list_std.size(), list_s21.size());
  EXPECT_EQ(*it, *it2);
  list_std.pop_front();
  list_s21.pop_front();
  it = list_std.begin();
  it2 = list_s21.begin();
  EXPECT_EQ(list_std.size(), list_s21.size());
  EXPECT_EQ(*it, *it2);
}

TEST_F(TestList, Test_PopBack) {
  auto it = list_std.end();
  auto it2 = list_s21.end();
  EXPECT_EQ(list_std.size(), list_s21.size());
  EXPECT_EQ(*(++it), *(++it2));
  list_std.pop_back();
  list_s21.pop_back();
  EXPECT_EQ(list_std.size(), list_s21.size());
  EXPECT_EQ(*(++it), *(++it2));
}

TEST_F(TestList, Test_FrontBack) {
  EXPECT_EQ(list_char_std.front(), list_char_s21.front());
  EXPECT_EQ(list_char_std.back(), list_char_s21.back());
}

TEST_F(TestList, Test_Insert) {
  auto it = --list_str_std.end();
  auto it2 = --list_str_s21.end();
  list_str_std.insert(it, "School");
  list_str_s21.insert(it2, "School");
  it = list_str_std.begin();
  for (auto i = list_str_std.begin(); i != list_str_std.end(); ++i, ++it) {
    EXPECT_EQ(*it, *i);
  }
  EXPECT_EQ(list_str_std.size(), list_str_s21.size());
}

TEST_F(TestList, Test_Clear) {
  list_std.clear();
  list_s21.clear();
  auto it = list_std.end();
  auto it2 = list_s21.end();
  EXPECT_EQ(*it, *it2);
  EXPECT_EQ(list_std.size(), list_s21.size());
}

TEST_F(TestList, Test_Erase) {
  auto it = ++list_std_2.begin();
  auto it2 = ++list_s21_2.begin();
  list_std_2.erase(it);
  list_s21_2.erase(it2);
  EXPECT_EQ(list_std_2.size(), list_s21_2.size());
  it2 = list_s21_2.begin();
  for (auto i = list_std_2.begin(); i != list_std_2.end(); ++i, ++it2) {
    EXPECT_EQ(*it2, *i);
  }
}

TEST_F(TestList, Test_Swap) {
  std::list<char> list1;
  s21::list<char> list2;
  list1.swap(list_char_std);
  list2.swap(list_char_s21);
  auto it1 = list1.begin();
  auto it2 = list2.begin();
  auto it22 = list_char_s21.begin();
  EXPECT_EQ(list1.size(), list2.size());
  EXPECT_EQ(list_char_std.size(), list_char_s21.size());
  for (auto it11 = list_char_std.begin(); it11 != list_char_std.end();
       ++it11, ++it1, ++it2, ++it22) {
    EXPECT_EQ(*it1, *it2);
    EXPECT_EQ(*it11, *it22);
  }
}

TEST_F(TestList, Test_Merge) {
  list_std_2.merge(list_std_3);
  list_s21_2.merge(list_s21_3);
  EXPECT_EQ(list_std_3.size(), list_s21_3.size());
  auto it = list_std_2.begin();
  for (auto i = list_std_2.begin(); i != list_std_2.end(); ++i, ++it) {
    EXPECT_EQ(*i, *it);
  }
}

TEST_F(TestList, Test_Splice) {
  auto it1 = std_kazan.begin();
  ++it1;
  std_kazan.splice(it1, std_school);
  auto it2 = s21_kazan.begin();
  ++it2;
  s21_kazan.splice(it2, s21_school);
  it1 = std_kazan.begin();
  it2 = s21_kazan.begin();
  EXPECT_EQ(std_school.size(), s21_school.size());
  for (; it1 != std_kazan.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_Reverse) {
  list_std_4.reverse();
  list_s21_4.reverse();
  auto it2 = list_s21_4.begin();
  for (auto it1 = list_std_4.begin(); it1 != list_std_4.end(); ++it2, ++it1) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_Unique) {
  list_char_std_2.unique();
  list_char_s21_2.unique();
  auto it1 = list_char_std_2.begin();
  EXPECT_EQ(list_char_std_2.size(), list_char_s21_2.size());
  for (auto it2 = list_char_s21_2.begin(); it2 != list_char_s21_2.end();
       ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_Sort) {
  list_char_std_3.sort();
  list_char_s21_3.sort();
  auto it1 = list_char_std_3.begin();
  EXPECT_EQ(list_char_std_3.size(), list_char_s21_3.size());
  for (auto it2 = list_char_s21_3.begin(); it2 != list_char_s21_3.end();
       ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_InsertMany) {
  std::list<int> std_lst{1, 2, 3, 4, 5};
  auto std_it = std_lst.begin();
  ++std_it;
  ++std_it;
  auto std_i = std_it;
  for (int data = 6; data < 9; ++data) {
    std_i = std_lst.insert(std_it, data);
  }
  s21::list<int> s21_lst{1, 2, 3, 4, 5};
  auto s21_it = s21_lst.begin();
  ++s21_it;
  ++s21_it;
  auto s21_i = s21_lst.insert_many(s21_it, 6, 7, 8);
  std_it = std_lst.begin();
  for (s21_it = s21_lst.begin(); s21_it != s21_lst.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
  EXPECT_EQ(*s21_i, *std_i);

  for (int data = -2; data < 1; ++data) {
    std_lst.push_front(data);
  }
  s21_lst.insert_many_front(-2, -1, 0);
  std_it = std_lst.begin();
  for (s21_it = s21_lst.begin(); s21_it != s21_lst.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }

  for (int data = 10; data < 15; ++data) {
    std_lst.push_back(data);
  }
  s21_lst.insert_many_back(10, 11, 12, 13, 14);
  std_it = std_lst.begin();
  for (s21_it = s21_lst.begin(); s21_it != s21_lst.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

// Set

class SetTest : public ::testing::Test {
public:
  s21::set<int> empty_set;
  std::set<int> empty_set_std;
  s21::set<int> int_set = {4, 8, 15, 16, 23, 42};
  std::set<int> int_set_std = {4, 8, 15, 16, 23, 42};
  s21::set<char> char_set = {'a', 'b', 'c'};
  std::set<char> char_set_std = {'a', 'b', 'c'};
  s21::set<std::string> string_set = {"one", "two", "three"};
  std::set<std::string> string_set_std = {"one", "two", "three"};
  s21::set<int> first = {4, 8, 15, 16, 23, 42};
  std::set<int> first_std = {4, 8, 15, 16, 23, 42};
  s21::set<int> second = {1, 2, 3, 4};
  std::set<int> second_std = {1, 2, 3, 4};
};

TEST_F(SetTest, TestDefaultConstructor) { EXPECT_TRUE(empty_set.empty()); }

TEST_F(SetTest, TestInitializerList) {
  EXPECT_EQ(int_set.size(), int_set_std.size());
}

TEST_F(SetTest, TestCopyConstructor) {
  s21::set<int> copy_set(int_set);
  auto i = int_set.begin();
  auto j = copy_set.begin();
  while (i != int_set.end() && j != copy_set.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(SetTest, TestMoveConstructor) {
  s21::set<char> copy_set(std::move(char_set));
  std::set<char> copy_set_std(std::move(char_set_std));
  EXPECT_EQ(char_set.empty(), char_set_std.empty());
  EXPECT_EQ(copy_set.size(), copy_set_std.size());
}

TEST_F(SetTest, TestCopyOperator) {
  s21::set<int> copy_set = int_set;
  auto i = int_set.begin();
  auto j = copy_set.begin();
  while (i != int_set.end() && j != copy_set.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(SetTest, TestMoveOperator) {
  s21::set<char> copy_set = std::move(char_set);
  std::set<char> copy_set_std = std::move(char_set_std);
  EXPECT_EQ(char_set.empty(), char_set_std.empty());
  EXPECT_EQ(copy_set.size(), copy_set_std.size());
}

TEST_F(SetTest, TestEmpty) { EXPECT_TRUE(empty_set.empty()); }

TEST_F(SetTest, TestSize) {
  EXPECT_EQ(string_set.size(), string_set_std.size());
}

TEST_F(SetTest, TestMaxSize) {
  EXPECT_EQ(int_set.max_size(), int_set_std.max_size());
}

TEST_F(SetTest, TestClear) {
  string_set.clear();
  string_set_std.clear();
  EXPECT_EQ(string_set.empty(), string_set_std.empty());
  EXPECT_EQ(string_set.size(), string_set_std.size());
}

TEST_F(SetTest, TestInsert) {
  int_set.insert(36);
  int_set_std.insert(36);
  auto i = int_set.begin();
  std::set<int>::iterator j = int_set_std.begin();
  while (i != int_set.end() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(SetTest, TestErase) {
  int_set.erase(int_set.begin());
  int_set_std.erase(int_set_std.begin());
  auto i = int_set.begin();
  std::set<int>::iterator j = int_set_std.begin();
  while (i != int_set.end() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.size(), int_set_std.size());
}

TEST_F(SetTest, TestSwap) {
  int_set.swap(empty_set);
  int_set_std.swap(empty_set_std);
  auto i = empty_set.begin();
  std::set<int>::iterator j = empty_set_std.begin();
  while (i != empty_set.end() && j != empty_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.size(), int_set_std.size());
  EXPECT_EQ(empty_set.size(), empty_set_std.size());
  EXPECT_TRUE(int_set.empty());
}

TEST_F(SetTest, TestMerge) {
  first.merge(second);
  first_std.merge(second_std);
  auto i = first.begin();
  std::set<int>::iterator j = first_std.begin();
  while (i != first.end() && j != first_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(first.size(), first_std.size());
}

TEST_F(SetTest, TestFind) {
  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(*(second.find(i)), *(second_std.find(i)));
  }
}

TEST_F(SetTest, TestContains) {
  for (int i = 1; i < 5; i++) {
    EXPECT_TRUE(second.contains(i));
  }
}

// Multiset

class MultisetTest : public ::testing::Test {
public:
  s21::multiset<int> empty_set;
  std::multiset<int> empty_set_std;
  s21::multiset<int> int_set = {4, 8, 15, 16, 23, 42};
  std::multiset<int> int_set_std = {4, 8, 15, 16, 23, 42};
  s21::multiset<char> char_set = {'a', 'b', 'c'};
  s21::multiset<std::string> string_set = {"one", "two", "three"};
  std::multiset<std::string> string_set_std = {"one", "two", "three"};
  s21::multiset<int> first = {4, 8, 15, 16, 23, 42};
  std::multiset<int> first_std = {4, 8, 15, 16, 23, 42};
  s21::multiset<int> second = {1, 2, 3, 4, 8};
  std::multiset<int> second_std = {1, 2, 3, 4, 8};
  s21::multiset<int> int_set2 = {1, 2, 2, 3, 4, 5, 5, 5, 5};
  std::multiset<int> int_set2_std = {1, 2, 2, 3, 4, 5, 5, 5, 5};
};

TEST_F(MultisetTest, TestDefaultConstructor) { EXPECT_TRUE(empty_set.empty()); }

TEST_F(MultisetTest, TestInitializerList) {
  EXPECT_EQ(int_set.size(), int_set_std.size());
}

TEST_F(MultisetTest, TestCopyConstructor) {
  s21::multiset<int> copy_set(int_set);
  auto i = int_set.begin();
  auto j = copy_set.begin();
  while (i != int_set.end() && j != copy_set.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MultisetTest, TestMoveConstructor) {
  s21::multiset<char> copy_set(std::move(char_set));
  EXPECT_TRUE(char_set.empty());
  EXPECT_EQ(copy_set.size(), 3);
}

TEST_F(MultisetTest, TestCopyOperator) {
  s21::multiset<int> copy_set = int_set;
  auto i = int_set.begin();
  auto j = copy_set.begin();
  while (i != int_set.end() && j != copy_set.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MultisetTest, TestMoveOperator) {
  s21::multiset<char> copy_set = std::move(char_set);
  EXPECT_TRUE(char_set.empty());
  EXPECT_EQ(copy_set.size(), 3);
}

TEST_F(MultisetTest, TestEmpty) { EXPECT_TRUE(empty_set.empty()); }

TEST_F(MultisetTest, TestSize) {
  EXPECT_EQ(string_set.size(), string_set_std.size());
}

TEST_F(MultisetTest, TestMaxSize) {
  EXPECT_EQ(int_set.max_size(), int_set_std.max_size());
}

TEST_F(MultisetTest, TestClear) {
  string_set.clear();
  string_set_std.clear();
  EXPECT_EQ(string_set.empty(), string_set_std.empty());
  EXPECT_EQ(string_set.size(), string_set_std.size());
}

TEST_F(MultisetTest, TestInsert) {
  int_set.insert(16);
  int_set_std.insert(16);
  auto i = int_set.begin();
  std::multiset<int>::iterator j = int_set_std.begin();
  while (i != int_set.end() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MultisetTest, TestErase) {
  int_set.erase(int_set.begin());
  int_set_std.erase(int_set_std.begin());
  auto i = int_set.begin();
  std::multiset<int>::iterator j = int_set_std.begin();
  while (i != int_set.end() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.size(), int_set_std.size());
}

TEST_F(MultisetTest, TestSwap) {
  int_set.swap(empty_set);
  int_set_std.swap(empty_set_std);
  auto i = empty_set.begin();
  std::multiset<int>::iterator j = empty_set_std.begin();
  while (i != empty_set.end() && j != empty_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.size(), int_set_std.size());
  EXPECT_EQ(empty_set.size(), empty_set_std.size());
  EXPECT_TRUE(int_set.empty());
}

TEST_F(MultisetTest, TestMerge) {
  first.merge(second);
  first_std.merge(second_std);
  auto i = first.begin();
  std::multiset<int>::iterator j = first_std.begin();
  while (i != first.end() && j != first_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(first.size(), first_std.size());
}

TEST_F(MultisetTest, TestCount) {
  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(int_set2.count(i), int_set2_std.count(i));
  }
}

TEST_F(MultisetTest, TestFind) {
  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(*(second.find(i)), *(second_std.find(i)));
  }
}

TEST_F(MultisetTest, TestContains) {
  for (int i = 1; i < 5; i++) {
    EXPECT_TRUE(second.contains(i));
  }
}

TEST_F(MultisetTest, TestEqualRange) {
  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(*(second.equal_range(i).first),
              *(second_std.equal_range(i).first));
    EXPECT_EQ(*(second.equal_range(i).second),
              *(second_std.equal_range(i).second));
  }
}

TEST_F(MultisetTest, TestLowerBound) {
  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(*(second.lower_bound(i)), *(second_std.lower_bound(i)));
  }
}

TEST_F(MultisetTest, TestUpperBound) {
  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(*(second.upper_bound(i)), *(second_std.upper_bound(i)));
  }
}

// Map

class MapTest : public ::testing::Test {
public:
  s21::map<int, char> empty_map;
  std::map<int, char> std_empty_map;
  s21::map<int, int> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, std::string> string_map = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> string_map_std = {
      {1, "one"}, {2, "two"}, {3, "three"}};
};

TEST_F(MapTest, TestDefaultConstructor) { EXPECT_TRUE(empty_map.empty()); }

TEST_F(MapTest, TestInitializerList) {
  EXPECT_EQ(my_map.size(), std_map.size());
}

TEST_F(MapTest, TestCopyConstructor) {
  s21::map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> copy_map(my_map2);
  auto i = my_map2.begin();
  auto j = copy_map.begin();
  EXPECT_EQ(my_map2.size(), copy_map.size());
  while (i != my_map2.end() && j != copy_map.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestMoveConstructor) {
  s21::map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> copy_map(std::move(my_map2));
  EXPECT_TRUE(my_map2.empty());
  EXPECT_EQ(copy_map.size(), 3);
}

TEST_F(MapTest, TestCopyOperator) {
  s21::map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> copy_map = my_map2;
  auto i = my_map2.begin();
  auto j = copy_map.begin();
  while (i != my_map2.end() && j != copy_map.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestMoveOperator) {
  s21::map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> copy_map = std::move(my_map2);
  EXPECT_TRUE(my_map2.empty());
  EXPECT_EQ(copy_map.size(), 3);
}

TEST_F(MapTest, TestAt) {
  for (int i = 1; i <= 3; i++) {
    EXPECT_EQ(my_map.at(i), std_map.at(i));
  }
}

TEST_F(MapTest, TestReferenceOperator) {
  for (int i = 1; i <= 3; i++) {
    EXPECT_EQ(my_map[i], std_map[i]);
  }
}

TEST_F(MapTest, TestEmpty) {
  EXPECT_EQ(empty_map.empty(), std_empty_map.empty());
}

TEST_F(MapTest, TestSize) {
  EXPECT_EQ(string_map.size(), string_map_std.size());
}

TEST_F(MapTest, TestMaxSize) {
  EXPECT_EQ(my_map.max_size(), std_map.max_size());
}

TEST_F(MapTest, TestClear) {
  string_map.clear();
  string_map_std.clear();
  EXPECT_EQ(string_map.empty(), string_map_std.empty());
  EXPECT_EQ(string_map.size(), string_map_std.size());
}

TEST_F(MapTest, TestInsertPair) {
  bool my_result = string_map.insert(std::pair{4, "four"}).second;
  bool std_result = string_map_std.insert(std::pair{4, "four"}).second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.begin();
  auto j = string_map_std.begin();
  while (i != string_map.end() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestInsertKeyValue) {
  bool my_result = string_map.insert(4, "four").second;
  bool std_result = string_map_std.insert(std::pair{4, "four"}).second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.begin();
  auto j = string_map_std.begin();
  while (i != string_map.end() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestInsertKeyValue2) {
  bool my_result = string_map.insert(2, "two").second;
  bool std_result = string_map_std.insert(std::pair{2, "two"}).second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.begin();
  auto j = string_map_std.begin();
  while (i != string_map.end() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(string_map.size(), string_map_std.size());
}

TEST_F(MapTest, TestInsertOrAssign) {
  bool my_result = string_map.insert_or_assign(3, "assign").second;
  bool std_result = string_map_std.insert_or_assign(3, "assign").second;
  EXPECT_EQ(my_result, std_result);
  my_result = string_map.insert_or_assign(4, "four").second;
  std_result = string_map_std.insert_or_assign(4, "four").second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.begin();
  auto j = string_map_std.begin();
  while (i != string_map.end() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestErase) {
  s21::map<int, char> my_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = my_map_2.begin();
  it++;
  auto it_std = std_map_2.begin();
  it_std++;
  my_map_2.erase(it);
  std_map_2.erase(it_std);
  s21::map<int, char>::iterator i = my_map_2.begin();
  std::map<int, char>::iterator j = std_map_2.begin();
  while (i != my_map_2.end() && j != std_map_2.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(my_map_2.size(), std_map_2.size());
}

TEST_F(MapTest, TestSwap) {
  s21::map<int, char> my_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  my_map_2.swap(empty_map);
  std_map_2.swap(std_empty_map);
  s21::map<int, char>::iterator i = empty_map.begin();
  std::map<int, char>::iterator j = std_empty_map.begin();
  while (i != empty_map.end() && j != std_empty_map.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(my_map_2.size(), std_map_2.size());
  EXPECT_EQ(empty_map.size(), std_empty_map.size());
  EXPECT_EQ(my_map_2.empty(), std_map_2.empty());
}

TEST_F(MapTest, TestMerge) {
  s21::map<int, char> first = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> first_std = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> second = {{2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'f'}};
  std::map<int, char> second_std = {{2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'f'}};
  first.merge(second);
  first_std.merge(second_std);
  s21::map<int, char>::iterator i = first.begin();
  std::map<int, char>::iterator j = first_std.begin();
  while (i != first.end() && j != first_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(first.size(), first_std.size());
}

TEST_F(MapTest, TestContains) {
  for (int i = 1; i <= 3; i++) {
    EXPECT_TRUE(my_map.contains(i));
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
