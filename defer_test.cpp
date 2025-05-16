#include <gtest/gtest.h>

#include <Defer.hpp>

#include <vector>

TEST(DeferTest, DeferExecutesOnScopeExit) {
  int x = 10;
  {
    defer(
      x = 20;
    );
    EXPECT_EQ(x, 10);
  }
  EXPECT_EQ(x, 20);
}

TEST(DeferTest, MultipleDefersExecuteInReverseOrder) {
  std::vector<int> v;
  {
    defer(v.push_back(1););
    defer(v.push_back(2););
    defer(v.push_back(3););
  }
  ASSERT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 3);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 1);
}

TEST(DeferTest, DeferWithEarlyReturn) {
  int x = 0;
  auto func = [&]() {
    defer(x = 42;);
    return;
  };
  func();
  EXPECT_EQ(x, 42);
}

TEST(DeferTest, DeferWithException) {
  int x = 0;
  try {
    defer(x = 99;);
    throw std::runtime_error("test");
  } catch (...) {
    // ignore
  }
  EXPECT_EQ(x, 99);
}

TEST(DeferTest, DeferDoesNotExecuteIfNotInScope) {
  int x = 0;
  if (false) {
    defer(x = 1;);
  }
  EXPECT_EQ(x, 0);
}

TEST(DeferTest, NestedDefers) {
  int x = 0;
  {
    defer(x += 1;);
    {
      defer(x += 10;);
    }
    EXPECT_EQ(x, 10);
  }
  EXPECT_EQ(x, 11);
}
