#include <gtest/gtest.h>

#include "bintree.hpp"
#include <cmath>

TEST(null, 1) {
  Node * bst = nullptr;
  
  EXPECT_TRUE( size(bst) == 0 );
  EXPECT_TRUE( max_height(bst) == 0 );
  EXPECT_TRUE( min_height(bst) == 0 );
  EXPECT_TRUE( is_balanced(bst) );

  EXPECT_THROW( find(bst, 10), std::out_of_range);
  EXPECT_THROW( edit(bst, 10), std::out_of_range);

  EXPECT_THROW( findMin(bst), std::out_of_range );
  EXPECT_THROW( findMax(bst), std::out_of_range );
  EXPECT_THROW( find(bst, 10), std::out_of_range );
}



TEST(size_1_tree, 1) {
  Node * bst = new Node();
  insert(bst, 10, 1.0);
  std::cout << bst << std::endl;

  EXPECT_TRUE( size(bst) == 1 );
  EXPECT_TRUE( max_height(bst) == 1 );
  EXPECT_TRUE( min_height(bst) == 1 );
  EXPECT_TRUE( is_balanced(bst) );

  EXPECT_TRUE( findNode(bst, 10) == bst );
  EXPECT_THROW( findNode(bst, 1), std::out_of_range );
  EXPECT_TRUE( findMin(bst) == bst );
  EXPECT_TRUE( findMax(bst) == bst );

  EXPECT_TRUE( find(bst, 10) == 1.0 );
  EXPECT_THROW( find(bst, 5), std::out_of_range );
  
  edit(bst, 10) = 3.0;
  EXPECT_THROW( edit(bst, 3), std::out_of_range );
  EXPECT_TRUE( find(bst, 10) == 3.0 );

  EXPECT_THROW( remove(bst, 1), std::out_of_range );

  remove(bst, 10);
  EXPECT_TRUE( bst == nullptr);
}



TEST(size_g1_tree, 1) {
  Node * bst = new Node();

  insert(bst, 18, 20.0);
  insert(bst, 27, 8.0);
  insert(bst, 10, 1.0);
  insert(bst, 99, 55.5);
  insert(bst, 21, 56.0);
  //        18:20.0
  //        |     |
  //   10:1.0     27:8.0
  //              |    |
  //         21:56.0  99:55.5

  EXPECT_TRUE( min_height(bst) == 2 );
  EXPECT_TRUE( max_height(bst) == 3 );
  EXPECT_TRUE( size(bst) == 5 );
  EXPECT_TRUE( is_balanced(bst) );
  EXPECT_TRUE( find(bst, 10) == 1.0 );
  edit(bst, 10) = 23.0;
  EXPECT_TRUE( find(bst, 10) == 23.0 );
  EXPECT_TRUE( size(findNode(bst, 27)) == 3 );

  /* Check unbalanced tree */
  insert(bst, 56, 100);
  EXPECT_TRUE( min_height(bst) == 2 );
  EXPECT_TRUE( max_height(bst) == 4 );
  EXPECT_TRUE( size(bst) == 6 );
  EXPECT_TRUE( !is_balanced(bst) );

  /* Test removal */
  std::cout << bst << std::endl;
  remove(bst, 27);
  std::cout << bst << std::endl;

  EXPECT_TRUE( size(bst) == 5 );
  EXPECT_TRUE( max_height(bst) == 3 );
  EXPECT_TRUE( min_height(bst) == 2 );
  EXPECT_TRUE( is_balanced(bst) );

  /* Test exception throwing */
  EXPECT_THROW( remove(bst, 5), std::out_of_range );
  EXPECT_THROW( find(bst, 5), std::out_of_range );
  EXPECT_THROW( edit(bst, 5), std::out_of_range );
  EXPECT_THROW( findNode(bst, 5), std::out_of_range );
    
  /* Delete tree */
  delete_tree(bst);

  EXPECT_TRUE( bst == nullptr );
}

int main (int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}