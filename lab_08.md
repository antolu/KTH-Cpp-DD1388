# Lab 8: Iterator class to binary tree

Implement an iterator class for a generic binary tree class. The
binary tree class is similar to the previous binary tree assignment.

```c++
template <class S, class T>
struct Node {
    typedef YOUR_ITERATOR iterator;             // TODO
    typedef YOUR_CONST_ITERATOR const_iterator; // TODO

    S key;
    T data;
    Node<S, T> * parent;    // points to parent node
    Node<S, T> * right;
    Node<S, T> * left;

    iterator begin();
    iterator end();
    const_iterator cbegin;
    const_iterator cend();

    iterator rbegin();
    iterator rend();

};
```

The _Node_ class should still be working with the functions written in
lab 3. You may need to adjust some methods to set the parent node
correctly. In a recursive _insert_ function it could be done just
after the recursive call:

```c++
  if ( key < p->key ) {
    insert(p->left, key, v);
    p->left->parent = p;
  } ...
```

The iterator shall satisfy a
[forwarditerator](http://en.cppreference.com/w/cpp/concept/ForwardIterator). You
can inherit from _forwarditerator_ and implement the following
methods:

```c++
Node<int, int>::iterator a;
Node<int, int>::iterator b(a);
b = a;
a == b
a != b
*a
a->member         // assumes the data field has a member _member_
*a = t
++a               // prefix
a++               // postfix
*a++
std::swap(a,b)
```

## access the data

When dereferencing the iterator, the data field of the Node is returned.

```c++
    Node<int, int> * P = nullptr;
    insert(P, 1, 'a');
    auto I = P->begin();
    *I = 5;             // sets the data field (3) to 'b'
```

The operator-> can be used on the pointer P if the Nodes data type is a class.
This is a substitute to the more inconvenient dereferencing and member access
`(*P).begin()`, which has the same result.

## iterating in order

Iterating over the tree should be done in order. The code below
should yield the same output order three times.

```c++
void print_inorder(Node<S, T> * p) {
    if (p != nullptr) {
        print_inorder(p->left);
        cout << p->data << endl;
        print_inorder(p->right);
    }
}
//...
{
    Node<..., ...> * root;
    insert(root, ...
    /....

    // first print
    print_inorder(root);

    // second print
    for (auto p = root->begin(); p != root->end(); ++p) {
        cout << *p << endl;
    }

    // third print (exactly the same code as above)
    for (auto q = root->begin(); q != root->end(); ++q) {
        cout << *q << endl;
    }
}
```

* _begin_ should return the leftmost Node. Performance should be of
order O(log N).

```
               6
              / \
   begin ->  1
              \
```

* _operator++_ You need to write **both** the prefix and the postfix
  version. Performance should be no worse than O(log N). Note that operator++ must support chaining.

* _end_ and _rend_ needs to return something reasonable. You may use _nullptr_
  but beware that the tree is full of _nullptr_.

* _rbegin_ should return the rightmost Node. This will change the behavior of operator++
  The code below prints the tree in reverse inorder.

```
    for (auto p = root->rbegin(); p != root->rend(); ++p)
        cout << *p << endl;
```


## Algorithm for tree traversal

You will need to keep track of the previously visited node. If there
is a right child, search for the next node in the left-most child of
the right child.

```
    current ->  6
               / \
                  9
                 /
                8
               /
              7   <- next
```

If there is no right node to explore, search for the next node
following the parent pointer. Keep following the parent pointer as
long as you are returning from a right child.

```
    next   ->  6
              / \
             1
              \
               2
                \
                 3  <- current
```

# Alternative data structure
Instead of using a parent pointer, you may use some sort of data structure (deliberately left vague) to implement the tree traversal.

## Exploring *const_cast*

Explore if you can use
[const_cast](http://en.cppreference.com/w/cpp/language/const_cast) to
avoid code duplication.


## Tests

Test your code. Be sure to test const_iterator as well. Reuse appropriate tests from lab 3.

Create a makefile with the rule _make test_ that builds and runs your tests.

## Access rights

Make a new version of the Node class that only exposes the _key_ and _data_ field. Use the _friend_ keyword to set access for functions operating on _Node_ and your iterator classes.


## Questions

#### Is there another way of implementing the iterator class instead of inheriting from forward_iterator?




#### How do you keep track of which nodes you already visited when iterating?



#### What sort of access rights should you use on the Node class?



#### If your test classes needs access rights to private members, how should you manage that?



#### Is is possible to avoid code duplication using *const_cast*?


#### This assignment has forced you to write a Node class and functions that operates on the Node. The usual object oriented solution is to have a Binary tree class with member functions that operate on an internal Node class. What benefits would that solution have compared to the assignment?



#### What was the most difficult part of this assignment?
