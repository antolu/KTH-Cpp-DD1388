# Lab 3: Binary tree

For this lab you will create a struct that represents a binary node in a binary search tree. You will then create functions that operate on the tree. Note, it is not an object oriented solution, there shall be no methods in the struct. Knowledge on binarty trees are prerequisitives for this course, if needed do refresh your knowledge on [binary trees](https://en.wikipedia.org/wiki/Binary_search_tree). The assignment will give you practice on pointers, memory handling and references.

Read the whole assignment before you begin. Implement one function at a time and the
corresponding tests. Push your solution to git as you progress.

### Balancing the tree

You do not need to implement a self balancing tree ([AVL](https://en.wikipedia.org/wiki/AVL_tree) or [red-black](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) tree) if you finish and push a correct solution during the course. Implementing a self balancing tree is optional during the course but it is _mandatory_ after the course has finished in June.

## Files

* bintree.h contains the struct and functionsheaders
* bintree.cpp contains the function implementations
* testtree.cpp contains a testprogram for the tree (or use cxxtest)
* testbalance.cpp contains a testprogram for balance testing
* makefile contains (at least) make all, make tests, make bintree

### struct Node

```c++
struct Node {
    int key;
    double data;
    Node * right;
    Node * left;
};
```



### functions

```c++
void insert(Node * & p, int key, double to_be_inserted);
void remove(Node * & p, const int & key);
const double & find(Node * p, const int & to_be_found);
double & edit(Node * p, const int & to_be_changed);
void delete_tree(Node * & p);

unsigned int max_height(Node * p);
unsigned int min_height(Node * p);
unsigned int size(Node * p);
bool is_balanced(Node * p);
```

You may improve the parameter names and [cv-qualifiers](http://en.cppreference.com/w/cpp/language/cv) in the code above.

In addition you could implement additional data types or help functions
such as *print_tree* or *look_for_maximum_replacement*.

### Implementation

Appropriate functions shall throw *std::out_of_range* if the key looked for is not in the tree.

* insert - Inserts key and value in the binary tree, initialize the new nodes left and right to nullptr. If the key already exists the value is overwritten, duplicate keys are not allowed. Key is required to have implemented _operator<_
* find - Find the node with key and returns it associated data.
* edit - Find and return a reference to editable data associated with the key.
* delete_tree - Deletes the entire tree at p.
* max_height - returns the height (longest chain) of the tree
* min_height - returns the shortest chain of the tree
* size - returns the number of nodes (p included) in the tree
* is_balanced - returns true if the tree is balanced
* remove - Remove the node with this key. If the node has two children you need to
  either find the find the maximum node to left or the minimum node to the right. Copy
  that node to the node with the key to be deleted and remove the found
  minimum/maximum node instead.

```
Example: remove key M (top node) from the following tree. Look for
the biggest key in the left sub tree which is K

          M
    B         R
  A   D
        K
       H


Copy that (K) nodes data to the top node

          K
    B         R
  A   D
        K
       H

Now remove the node with K. In this example that node have only one child (H)
which, when K is deleted, would be moved upwards.

          K
    B         R
  A   D
        H

Be aware that you need to adjust D's right pointer (call remove with the approriate
pointer) in the D node so its right pointer is properly adjusted after removal of K.
```


### Makefile

Create a _makefile_ with at least the following rules.

* _make bintree_ compiles your binary tree functions
* _make all_ compiles your bintree functions and your testprograms
* _make tests_ runs all your testprograms



## Tests

Create a file _testtree.cpp_ that tests your implementation. Use
valgrind to catch memory bugs. Do the following tests.

* Test eligble functions with an empty tree (call with nullptr)
* Test *all* functions for correctness with a tree of size 1
* Tests some functions for correctness with a tree size > 1
* Test some functions if they properly throw std::out_of_range with a tree size > 1
* Optional template struct: Do some tests with a custom key class that has only operator< defined.

Write one(!) _informative_ line to std::cout for each test alternatively use cxx_test for testing

Induce one or more bugs in your code and run your tests. Correct the bug(s) afterwards.

### Test tree balance

Create a file _testbalance.cpp_ that tests how the tree is balanced.

Create a std::vector of size 9000 containing the
values 1, 2, 3, 4 ... 9000. Use [std::shuffle](http://www.cplusplus.com/reference/algorithm/shuffle/)
to shuffle the numbers. Set a random _seed_ to your birthday (YYMMDD) to ensure the
same random sequence when testing.

Create a std::vector or std::array of size 800 to save results
from the following tests

Do the following 800 times

* Create a new binary tree of integers (_Node * root_)
* Insert the shuffled integers into the tree using the integer as
  both key and value
* call max_height and min_height and save the results
* use [next_permutation](http://www.cplusplus.com/reference/algorithm/next_permutation/) to reshuffle the 9000 integers. Do note how next_permutation reshuffles.
* repeat

Report the following on stdout, use two decimals for average output.

* The average height of the tree in 800 iterations
* The highest maximum height
* The average minimum height
* The lowest minimum height
* The average difference between minimum and maximum height
* The greatest difference between minimum and maximum height
* The lowest difference between minimum and maximum height

_Note_, only the final run need be 800 * 9000 do use smaller numbers while developing.

### Improve testing

See if you can improve the reshuffling and if you get different
results. Does it effect testing time?

### Optional assignment - template double linked tree

Later on there will be an extra assignment which uses a double linked template tree.

```c++
template <class S, class T>
struct Node {
    S key;
    T data;
    Node<S, T> * parent;
    Node<S, T> * right;
    Node<S, T> * left;
};
```

A recursive _insert_ will probably have to set _parent_ after a recursive call.

```c++
...
   insert(parameter->right, key, value);
   parameter->right->parent = parameter;
...
```


### Optional/mandatory assignment - self balancing tree

Implement a self balancing tree and rerun the previous balancing tests. Add
testing that removes sample nodes. This assignment is optional during the course but mandatory if you have not pushed a tested binary search tree
to your git repository during the course. Use the previous template struct and appropriate help functions.

#### Questions

Create an inquiry_03 in the 03 sub folder

```
> touch 03/inquiry.md
```

Copy the questions below and write your answers in 03/inquiry.md in markdown-format.

#### If the signature of _insert_ was changed like below, how would that affect your code?

```
Node * insert(Node * p, int key, double value);
```

#### Which of the two _insert_ variants would you prefer? Motivate.



#### How that your are able to pass a value, such as 17, to a _const int & parameter_ ?



#### How do you check if two objects are equal if they only have operator< and not operator==?

#### Does _a < b_ and _!(b < a)_ compare the same thing?

#### What was hardest to implement in this assignment?


#### What did you learn from this asignment?
