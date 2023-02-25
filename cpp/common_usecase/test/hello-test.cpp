#include "gtest/gtest.h"
#include "main/hello-greet.hpp"

TEST(HelloTest, GetGreet) {
    EXPECT_EQ(get_greet("Bazel"), "Hello Bazel");
}
