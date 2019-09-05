## How many methods/functions have you implemented?
50

## How many methods/functions have you tested?
All of them (hopefully).

## Why should (some?) constructors be explicit? Explain with a code example.
A constructor taking one argument should be declared explicit when...

## What is the benefit of a move-constructor? Explain with a code example.
Saves on memory, can move non-copyable data types. 

## Describe how you manage memory when resizing. When do you need to resize?
Always resize when extending a matrix (making it bigger), because arrays cannot grow dynamically. 

Resize is performed by allocating a whole new internal array and moving elements from the current array. 

When shrinking (removing columns or rows), the internal array does not get shrunk or reallocated for efficiency. However this leaves empty elements dangling at the end of the array. 

## Why do you need to implement a const-version of the accessor operator?
## If you type define the return type of begin/end as iterators is it possible to call std::sort() to sort your matrix?


## What kind of iterator is begin/end?
Pointers. Pointers to the first and after-last-element of the internal array. 

## What other kind of iterators are there? Is there any you would like to implement?
idk lol

## What was hardest to implement in this assignment?
Transpose(), and column-manipulations because the internal representation is row-major. 

## What did you learn from this assignment?
Handling dynamic arrays, templates in header files, operator(). (I have implemented matrix classes before). 
