#include "fms.h"
#include <gtest/gtest.h>

// 測試 FMS 函式的行為
TEST(FMSTest, BasicInput) {
  char s[] = "rate R2D2 2 time 55566 23 12 #";
  char expOutput[] = "rate - identifier\nR2D2 - identifier\n2 - number\ntime - "
                     "identifier\n55566 - number\n23 - number\n12 - number\n";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMTEST, UUU) {
  char s[] = "";
  char expOutput[] = "";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSETEST, UUEU) { ASSERT_STREQ("123", "123"); }

TEST(FMSTST, UUjU) {
  char s[] = "123 -+ 34 U";
  char expOutput[] = "123 - number\n-";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTest, Identifier) {
  char s[] = "abc def";
  char expOutput[] = "abc - identifier\ndef";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTest, Number) {
  char s[] = "123 456";
  char expOutput[] = "123 - number\n456";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTest, MixedInput) {
  char s[] = "abc 123 def";
  char expOutput[] = "abc - identifier\n123 - number\ndef";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTest, NoOutput) {
  char s[] = "   ";
  char expOutput[] = "";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSfTest, NoOutput) {
  char s[] = "abc # ty 45 dty";
  char expOutput[] = "abc - identifier\n";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSggTest, NoOuut) {
  char s[] = "#";
  char expOutput[] = "";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTeshht, Ntput) {
  char s[] = "_";
  char expOutput[] = "_";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTeshht, Ntoooput) {
  char s[] = "0";
  char expOutput[] = "0";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTeshht, Ntouuooput) {
  char s[] = "abc 123 # xyz";
  char expOutput[] = "abc - identifier\n123 - number\n";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTeshht, put) {
  char s[] = "abc123 def456";
  char expOutput[] = "abc123 - identifier\ndef456";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTeshht, Ntooot) {
  char s[] = "###";
  char expOutput[] = "";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTeshht, Ntoot) {
  char s[] = "!@#$%^&*()";
  char expOutput[] = "!";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTest, Ntoppot) {
  char s[] = "abc #";
  char expOutput[] = "abc - identifier\n";
  ASSERT_STREQ(expOutput, FMS(s));
}

TEST(FMSTest, MultipleNumbersIdentifiersInputString) {
  char s[] = "123 abc 456 def";
  char expOutput[] = "123 - number\nabc - identifier\n456 - number\ndef";
  ASSERT_STREQ(expOutput, FMS(s));
}

// 定義 main 函式
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
