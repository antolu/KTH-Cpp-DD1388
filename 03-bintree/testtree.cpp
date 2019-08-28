#include <catch2/catch.hpp>

#include "bintree.hpp"
#include <cmath>

TEST_CASE("nullptr") {
  Node * bst = nullptr;
  
  CHECK( size(bst) == 0 );
  CHECK( max_height(bst) == 0 );
  CHECK( min_height(bst) == 0 );
  CHECK( is_balanced(bst) );

  CHECK_THROWS_AS( find(bst, 10), std::out_of_range);
  CHECK_THROWS_AS( edit(bst, 10), std::out_of_range);

  CHECK_THROWS_AS( findMin(bst), std::out_of_range );
  CHECK_THROWS_AS( findMax(bst), std::out_of_range );
  CHECK_THROWS_AS( find(bst, 10), std::out_of_range );
}



TEST_CASE("Size 1 tree") {
  Node * bst = new Node();
  insert(bst, 10, 1.0);
  std::cout << bst << std::endl;

  CHECK( size(bst) == 1 );
  CHECK( max_height(bst) == 1 );
  CHECK( min_height(bst) == 1 );
  CHECK( is_balanced(bst) );

  CHECK( findNode(bst, 10) == bst );
  CHECK_THROWS_AS( findNode(bst, 1), std::out_of_range );
  CHECK( findMin(bst) == bst );
  CHECK( findMax(bst) == bst );

  CHECK( find(bst, 10) == 1.0 );
  CHECK_THROWS_AS( find(bst, 5), std::out_of_range );
  
  edit(bst, 10) = 3.0;
  CHECK_THROWS_AS( edit(bst, 3), std::out_of_range );
  CHECK( find(bst, 10) == 3.0 );

  CHECK_THROWS_AS( remove(bst, 1), std::out_of_range );

  remove(bst, 10);
  CHECK( bst == nullptr); 
}



TEST_CASE("Size >1 tree") {
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

  CHECK( min_height(bst) == 2 );
  CHECK( max_height(bst) == 3 );
  CHECK( size(bst) == 5 );
  CHECK( is_balanced(bst) );
  CHECK( find(bst, 10) == 1.0 );
  edit(bst, 10) = 23.0;
  CHECK( find(bst, 10) == 23.0 );
  CHECK( size(findNode(bst, 27)) == 3 );

  /* Check unbalanced tree */
  insert(bst, 56, 100);
  CHECK( min_height(bst) == 2 );
  CHECK( max_height(bst) == 4 );
  CHECK( size(bst) == 6 );
  CHECK( !is_balanced(bst) );

  /* Test removal */
  std::cout << bst << std::endl;
  remove(bst, 27);
  std::cout << bst << std::endl;

  CHECK( size(bst) == 5 );
  CHECK( max_height(bst) == 3 );
  CHECK( min_height(bst) == 2 );
  CHECK( is_balanced(bst) );

  /* Test exception throwing */
  CHECK_THROWS_AS( remove(bst, 5), std::out_of_range );
  CHECK_THROWS_AS( find(bst, 5), std::out_of_range );
  CHECK_THROWS_AS( edit(bst, 5), std::out_of_range );
  CHECK_THROWS_AS( findNode(bst, 5), std::out_of_range );
    
  /* Delete tree */
  delete_tree(bst);

  CHECK( bst == nullptr );
}
