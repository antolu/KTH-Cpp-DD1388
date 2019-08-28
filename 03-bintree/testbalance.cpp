#include <catch2/catch.hpp>

#include "bintree.hpp"
#include <algorithm>
#include <random>
#include <vector>

TEST_CASE("Balance") {
  // std::vector<int> keys(9000, 0);

  // for (int i = 1; i <= 9000; i++)
  //   keys[i-1] = i;

  // int seed = 960611;
  // std::shuffle(std::begin(keys), std::end(keys), std::default_random_engine(seed));

  // int max_res [800];
  // int min_res [800];
  // Node * bst = nullptr;
  // for (int j = 0; j < 800; j++) {
  //   bst = new Node();
  //   for (int k = 0; k < 9000; k++)
  //     insert(bst, keys[k], k);

  //   max_res[j] = max_height(bst);
  //   min_res[j] = min_height(bst);
  //   delete_tree(bst);

  //   std::next_permutation(std::begin(keys), std::end(keys));
  // }
  
  // /* Average height */
  // int avg = 0;
  // for (int i = 0; i < 800; i++)
  //   avg += max_res[i];

  // std::cout << "Average height: " << avg / 800. << std::endl;

  // std::cout << "Maximum height: " << *std::max_element(std::begin(max_res), std::end(max_res)) << std::endl;

  // /* Average height */
  // int avg_min = 0;
  // for (int i = 0; i < 800; i++)
  //   avg_min += min_res[i];

  // std::cout << "Average minumum height: " << avg_min / 800. << std::endl;

  // std::cout << "Minimum height: " << *std::min_element(std::begin(min_res), std::end(min_res)) << std::endl;

  // /* Average height diff */
  // int avg_diff = 0;
  // int diffs [800];
  // for (int i = 0; i < 800; i++) {
  //   avg_diff += (max_res[i] - min_res[i]);
  //   diffs[i] = (max_res[i] - min_res[i]);
  // }

  // std::cout << "Average height diff: " << avg_diff / 800. << std::endl;

  // std::cout << "Max height diff: " << *std::max_element(std::begin(diffs), std::end(diffs)) << std::endl;

  // std::cout << "Min height diff: " << *std::min_element(std::begin(diffs), std::end(diffs)) << std::endl;
}
