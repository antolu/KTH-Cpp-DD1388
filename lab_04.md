# Lab 4: The matrix

In this assignment you will implement a matrix class. You may need to refresh
your knowledge on basic matrix arithmetics. The matrix should be implemented
with an array (*m_vec*) which means you need to use some simple arithmetic to access
a matrix index (i, j). If the number of rows is only one, the matrix will essentially
behave like a vector. Random access to an element should be on average constant O(1).
The first element (0, 0) is at m_vec[0].

Appropriate methods should be declared *const*

Methods should throw std::out_of_range if the dimensions do not match the method call

The matrix should handle necessary memory allocation internally without
memory leaks. If the
matrix needs to expand, the internal vector must be resized. Use valgrind or fsanitize
to verify your code.

```c++
template <class T>
class Matris {
public:
   // constructors

   // operators

   // methods

private:
   size_t m_rows;
   size_t m_cols;
   size_t m_capacity;
   T * m_vec;
}
```

### Constructors and assignment operators

Some of this constructors might seem strange but they are here for you to practice C++.


* It should be possible to construct the matrix with a single number. The matrix
  created should be a square matrix with initial elements set to the default element
  of the type.

```
   Matris<int> m(3);
   m [ 0 0 0
       0 0 0
       0 0 0 ]
```

* It should be possible to _default-construct_ the container, which
  should be semantically equivalent to matrix<T>(0).


* You should implement a copy-constructor and a destructor. _Note_ modifying a copied
  matrix should not changed the contents of the copied-from matrix.

*   It should not be possible to instantiate the class template unless the
    specified element type is both *moveConstructible* and
    *moveAssignable*. Use _static_assert_ with an appropriate error message, to
    make sure that this is the case.

* Appropriate constructors should be explicit

* You should implement a copy-assignment operator, and although assigning
  a matrix to itself might seem silly, make sure it is handled correctly.


* Implement a move-constructor and a move-assignment operator taking another
   matrix potentially of a different size


* Implement a constructor taking _std::initializer_list_. This constructor can only
  construct square matrices. If the number of elements is not an even square root
  std::out_of_range should be thrown. The first elements defines the first row and
  then the next rows in sequence



### Accessors

* implement rows() and cols() which returns number of rows and columns respectively

* Implement the function operator to access/modify elements. Make a *const* version as well.

```c++
   Matris<int> m(3);
   m(1, 1) = 3;
   const Matris<int> & mref = m;
   std::cout << mref(1, 1);
```

### Operators

For both scalar and matrix operations:

* Implement * + - which should be chainable

* Implement *= += -= as non chainable.

Writing and reading from stdin and stdout in human friendly (readable) format

* Implement operator<< and operator>> and make them compatible. If you write to a
  file, you should be able to read the matrix from the same file. The exact format
  is up to you but do make it human readable (use a line break after each row).

### Methods/functions

* Implement _reset()_ method which sets all elements to the default value of the type. Default constructor T() can be assumed.

* Implement the function _identity(unsigned int)_ which returns a square identity
  matrix where all elements but
  the diagonal are set to 0 and the diagonal values to 1.

Implement the following [Mircosoft(R) Excel](https://en.wikipedia.org/wiki/Microsoft_Excel) inspired methods:

* Implement *insert_row* which inserts a row of zeroes before a given row number.

* Implement *append_row* which inserts a row of zeroes after a given row number.

* Implement *remove_row* which erases the entire row at a given row number

* Implement *insert_column* which inserts a column of zeroes before a given column number.

* Implement *append_column* which inserts a column of zeroes after a given column number.

* Implement *remove_column* which erases the entire column at a given column number

### Iterators, do typedef T* as iterator

* Implement *begin()* which returns the pointer to the first element of the matrix.

* Implement *end()* which returns the pointer to the element after the last element.

### Optional/mandatory method

If you are working on this assignment before june, do implement
the [_transpose()_](https://en.wikipedia.org/wiki/Transpose) of a matrix

```
m.transpose();

                      1 5
1 2 3 4  transposed   2 6
5 6 7 8     ->        3 7
                      4 8
```

If you have not pushed a tested solution to this assignment before the course
ends in June, you should *instead* of the _transpose()_ method implement
the _inverse_ method which inverses a matrix. Note that only square matrices
can have inverses (although not all do) throw std::out_of_range if there is
no inverse. If the matrix elements does not support the math to calculate
the inverse, a compile error should be given.

## Tests

For each method/function implemented. Implement at least one test (one method call).

Use cxx_test for testing

#### Questions

Copy inquiry_04.md to 04 sub folder

```
cp inquiry_04.md 04/inquiry.md
```

Write your answers in 04/inquiry.md


#### How many methods/functions have you implemented?


#### How many methods/functions have you tested?


#### Why should (some?) constructors be explicit? Explain with a code example.


#### What is the benefit of a move-constructor? Explain with a code example.


#### Describe how you manage memory when resizing. When do you need to resize?


#### Why do you need to implement a const-version of the accessor operator?

#### If you type define the return type of begin/end as iterators is it possible to call std::sort() to sort your matrix?

#### What kind of iterator is begin/end?

#### What other kind of iterators are there? Is there any you would like to implement?


#### What was hardest to implement in this assignment?


#### What did you learn from this assignment?
