//
// Created by anton on 5/26/20.
//

#include "gtest/gtest.h"
#include "count_if_followed_by.h"

TEST(cxxtest, cxxtest) {
    char const  data[6] = {'G','G','X','G','X','G'};
    int  const test_len = 4;

    int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

    // SYNOPSIS:
    //   result should be 1 since the length specified is 4,
    //   and only one pair of [X, G] is present in that range!

    EXPECT_EQ(result, 1);
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}