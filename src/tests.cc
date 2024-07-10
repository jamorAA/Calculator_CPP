#include <gtest/gtest.h>

#include "Model/model.h"

s21::Model model;

TEST(SmartCalc, Test1) {
  std::string str = "2";
  EXPECT_EQ(2, model.calculate(str, 0));
}

TEST(SmartCalc, Test2) {
  std::string str = "4+3";
  EXPECT_EQ(7, model.calculate(str, 0));
}

TEST(SmartCalc, Test3) {
  std::string str = "-4.2+(-2.5)";
  EXPECT_EQ(-6.7, model.calculate(str, 0));
}

TEST(SmartCalc, Test4) {
  std::string str = "4/x";
  EXPECT_EQ(2, model.calculate(str, 2));
}

TEST(SmartCalc, Test5) {
  std::string str = "4.2e2-10";
  EXPECT_EQ(410, model.calculate(str, 0));
}

TEST(SmartCalc, Test6) {
  std::string str = "cos(5)";
  EXPECT_NEAR(0.2836622, model.calculate(str, 0), 7);
}

TEST(SmartCalc, Test7) {
  std::string str = "2^3^(4-3)";
  EXPECT_EQ(8, model.calculate(str, 0));
}

TEST(SmartCalc, Test8) {
  std::string str = "cos(2.5)*3.1-22/4.3";
  EXPECT_NEAR(-7.5998244, model.calculate(str, 0), 7);
}

TEST(SmartCalc, Test9) {
  std::string str = "sin(2)*acos(0.22)/ln(3)";
  EXPECT_NEAR(1.11652, model.calculate(str, 0), 7);
}

TEST(SmartCalc, Test10) {
  std::string str = "(2-4)*(1-3)";
  EXPECT_EQ(4, model.calculate(str, 0));
}

TEST(SmartCalc, Test11) {
  std::string str = "(2-x)*(1-3)";
  EXPECT_EQ(4, model.calculate(str, 4));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}