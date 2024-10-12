#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../include/parent.h"
#include <cstdio>

TEST(test_01, lab1_test){
    std::ofstream file("test.txt");
    file << "100 10 2 " << std::flush;
    std::string a = ParentRoutine("test.txt");
    file.close();
    remove("test.txt");
    ASSERT_EQ(a, "5");
}

TEST(test_02, lab1_test){
    std::ofstream file("test.txt");
    file << "100 10 5 " << std::flush;
    std::string a = ParentRoutine("test.txt");
    file.close();
    remove("test.txt");

    ASSERT_EQ(a, "2");
}

TEST(test_03, lab1_tests){
    std::ofstream file("test.txt");
    file << "1000 2 2 5 2 " << std::flush;
    std::string a = ParentRoutine("test.txt");
    file.close();
    remove("test.txt");
    ASSERT_EQ(a, "25");
}