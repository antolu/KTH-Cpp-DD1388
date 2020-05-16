# Lab 5: Lambdas and smart pointers

In this assignement you will work with [lambdas](http://en.cppreference.com/w/cpp/language/lambda) and [smart pointers](http://en.cppreference.com/w/cpp/memory).

Copy this file to 05/lab_05.md in your git repository. Answer questions
directly in this file while you are doing the assignement.

#### Questions

#### What is a capture list in a lambda expression?
It's the variables that are made available to the scope of the lambda from the outer scope.

#### What does & mean inside the parameter list?

It means to capture all available variables by reference.

#### When could capturing data by reference [&] be useful?

When for instance one wants to edit a variable in the outer scope. For instance write to a logfile or stream upon callback.

#### What does {4} in the code below do?

```c++
        A * p = new A {4} ;
```

Initialise the pointer p using list initialisation with argument int: 4.

#### Why is it a compile error to call foo with a unique_ptr without a move?

```c++
        foo(pa);
```

Because the unique_ptr has to have unique ownership over the pointer.

#### Was there ever a memory leak when calling foo2 with a shared pointer?

No

#### What is the use of a weak_ptr?

Smart pointer that holds non-holding ownership of an object managed by shared_ptr. Must be converted to shared_ptr to access the referenced object.

#### How do you create a unique_ptr with a special deleter?

std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
Use the type `std::unique_ptr<T, some_deleter>` for type declaration, and use a function wrapper for the second argument of the constructor. 

#### What is _decltype_ ?

Inspects the declared type of an entity or the type and value category of an expression

#### What is std::function?

Function wrapper. instances of the class can copy, store, invoke any callable target: functions, lambdas etc.

#### What did you learn in this assignement?

Most importantly for me, the use of std::functions. This can be compared to python syntax where you can bind a function wrapper to a variable and pass it around.

Of course advanced pointer handling too, but I personally don't find that useful, yet..

You will need to include the following libraries in this
assignment. Namespace std:: is used for clarity.

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

```

## Lambdas

```c++
//...
{
    vector<int> v = {1, 3, 4, 5, 6, 7, 8, 9};
    // printing v
    cout << "vector v:" << endl;

    for (auto x : v) { cout << x << " "https://docs.google.com/document/u/0/;};
        cout << endl;
}
```

Write a for_each statement that uses a lambda expression to print
odd numbers in vector v.

```c++
    for_each(v.cbegin(), v.cend(), // YOUR LAMBDA HERE )
```

* Write another for_each statement that changes the values in v by

multipliying all odd numbers by 2.

* Write a for_each statement that changes the vector elements by

  adding the size of the vector to all elements.

* Write a lambda function on our own that changes any data of your choice

  outside the scope of the lambda by capturing with [ & ].

example:

```c++

   //...
   int OUTSIDEDATA

   // ....  [ & OUTSIDEDATA ]( // YOUR LAMBDA

```

## Pointers

The following code will be used

```c++
struct A {
    int data;

};

void foo(unique_ptr<A> p) {
    cout << p->data << endl;
}

void foo2(shared_ptr<A> p) {
    cout << p->data << endl;
}

```

Define a unique_ptr to A inside an arbitrary scope and print the data

```

    {
        unique_ptr<A> pa(new A {4} );
        cout << pa -> data;
```

Try calling _foo_ with your unique_ptr. There is a compile error. Why?

```
        foo(pa);
```

Fix the compile error by using move when callin foo. Run valgrind on
your executable and verify that there are no memory leaks.

### Shared ptr

Declare a shared pointer to A and print the data

```c++

        shared_ptr<A> sa(new A {5});
        cout << sa -> data;

```

Call foo2 first normally and then by moving. Run valgrind on both executables. Is there a memory leak?

```c++
        foo2(sa);            // check with valgrind
        //foo2(move(sa));    // check with valgrind
```

### Weak pointer

Constructing a weak pointer as a shared pointer generates a compile error

```C++

        weak_ptr<A> wa(new A {5});

```

Construct a weak pointer to the previous shared pointer and try print the
data. There will be a compile error.

```C++
        weak_ptr<A> wa = sa;
        cout << wa->data;
```

Use the _lock_ member function to print the data field.

### circular dependencies

Given BhasA and AhasB

```c++
struct BhasA; 

struct AhasB {

    AhasB(shared_ptr<BhasA> b) : m_b(b)  {
        resource = new int[4];
    };

    shared_ptr<BhasA> m_b;
    int * resource;

    ~AhasB() {delete [] resource;}
    AhasB(const AhasB &) = delete;
    void operator=(const AhasB &) = delete;

};

struct BhasA {

    BhasA() {resource = new int[4];};

    shared_ptr<AhasB> m_a;
    int * resource;

    ~BhasA() {delete [] resource;}
    BhasA(const BhasA &) = delete;
    void operator=(const BhasA &) = delete;

};

```

Declare one instance each of AhasB and BhasA and link them.

```C++
        shared_ptr<BhasA> bptr(new BhasA);
        shared_ptr<AhasB> aptr(new AhasB(bptr));

        bptr->m_a=aptr;
```

There is a memory leak when you run valgrind on the code. Why?

Fix the memory leak by changing one of the shared_ptr members to a weak pointer.

### Using a deleter

Given B

```c++
struct B {

    B() { b = new int[4]; }

    int * b;
    ~B() { delete [] b; }
    B(const B &) = delete;
    void operator= (const B & ) = delete;

};

```

There will a memory leak when declaring a unique_ptr as below. Verify
the memory leak with valgrind.

```c++
        unique_ptr<B> pb(new B[2]);
```

The memory leak is because the unique_ptr asumes it points to a single
object not to an array.

In order to fix the memory leak ýou need to create a function that
does a correct deletion of the objects.

Write a lambda function that does a correct deletion of the array

```c++

        auto deleter = // YOUR LAMBDA HERE
        unique_ptr<B, decltype(deleter)> pb2(new B[2], deleter);

```

If you know the signature of your lambda function you can declare it
with the _function_ keyword directly instead of using auto

```c++
        function<void(B*)> fb = // YOUR LAMBDA
```

It is thus possible to declare the unique_ptr in one row

```c++

        unique_ptr<B, function<void(B*)> > pb1(new B[2],  // YOUR LAMBDA

```

## A small concurrency example with a condition variable and lambda

Around a waterhole in Africa there is a huge cage with three
compartments, separated by gates according to this figure:

![alt text](HyenasAndGnus.jpg "A rectangle divided into three small rectangles by two vertical lines each spanning the full height of the rectangle. The left small rectangle is marked hyenas; the middle small rectangle is marked waterhole; and the right small rectangle is marked gnus.")

The left compartment is for the hyenas. The middle compartment is where the
water hole is. The right compartment is for gnus. Each animal will
sleep for a random amount of time then wake up to go and drink for a
random amount of time (smaller than sleeping) then go back to
sleep. If a gnu gets thirsty it may drink water if there are no hyenas
in the waterhole. A thirsty gnu that can't drink will have to wait. A
thirsty hyena may drink water if there are no gnus at the water
hole. The rules are enforced by opening and closing the gates between
each compartment.

The hyenas and gnus are simulated with threads where each thread is
initiated with either a gnu or a hyena function.

```c++
    vector<thread> threadvec;
    for (int i = 0; i < nrGnus; i++)
        threadvec.push_back(thread(gnu));
    for (int i = 0; i < nrHyenas; i++)
        threadvec.push_back(thread(hyena));
```

Upon creating the threads, the functions _gnu_ and _hyena_ will start running.
Join the threads with a similar loop

```c++
    for (int i = 0; i < nrGnus; i++)
        threadvec[i].join();
    for (int i = 0; i < nrHyenas; i++)
        threadvec[i].join();
```

and that is basically all your main simulating program needs to do.

### _gnu_ and _hyena_ functions

The _gnu_ and _hyena_ functions are almost identical

```C++
void gnu(//...) {
   while (// run a number of simulations
     // sleep for a while
	    watermanager.gnuEnters();            // see monitoring class below
        // drink water for a while i.e. sleep for a short while
	    watermanager.gnuLeaves();
```

Use
[this_thread::sleep_for](http://en.cppreference.com/w/cpp/thread/sleep_for)
to put the thread to sleep.

### A water manager class

Write a monitoring class WaterManager that has four methods.

* hyenaEnters
* gnuEnters
* hyenaLeaves
* gnuLeaves

Let WaterManager have
a [condition_variabe](http://en.cppreference.com/w/cpp/thread/condition_variable) CONDITIONVAR and
a [mutex](http://en.cppreference.com/w/cpp/thread/mutex) as well as
two atomic integers with the current number of hyenas or gnus inside (_hyenasInside_, _gnusInside_).

Upon entering, create a local lock
([unique_lock](http://en.cppreference.com/w/cpp/thread/unique_lock) or
[lock_guard](http://en.cppreference.com/w/cpp/thread/lock_guard)) SOMELOCK and
call the condition_variable's wait-method with the lock and a lambda function.

example: (do change CONDITIONVAR and SOMELOCK to appropriate varaiable names)

```C++

     // A gnu has to wait until there are no hyenas
     CONDITIONVAR.wait(SOMELOCK, [this] {return hyenasInside == 0;});
	gnusInside += 1;

``` 

Upon exiting, lock the WaterManagers mutex and update
_hyenasInside_/_gnusInside_. Then notify all threads with
the condition_variable's notify_all() method (CONDITIONVAR.notiy_all()).

### Trace outputs

Implement trace outputs that can easily be turned on or off. Decide if
turning trace outputs should be a compile option or a runtime option
or both.

Each thread has a unique id that can be reached with
[get_id](http://en.cppreference.com/w/cpp/thread/get_id).

#### use an unordered map

Instead of printing the thread id, create an
[unordered_map](http://en.cppreference.com/w/cpp/container/unordered_map)
with [thread::id](http://en.cppreference.com/w/cpp/thread/thread/id)
as key and a more human readable string (example Gnu nr 3) as value as you create the threads.
Use the mapped string in your trace outputs.

#### Iterating over an unordered map

Implement a loop over the map and print each key and value, take notice of the order
the items are printed.

Place significant trace outputs inside the _gnu_ and _hyena_ functions
so you can follow the code. An example is given below. Notice how
three hyenas have to wait until the cave is empty whereupon they all
enter. Experiment with different wait times and upload a few trace
outputs to git.

The trace outputs below only show the watercave status when any animal enters the
watercave. Make your own opinion if the status information below is enough.

```

Gnu 2 is thirsty
A gnu enters the watercave         hyenas = 0         gnu = 1
Gnu 3 is thirsty
A gnu enters the watercave         hyenas = 0         gnu = 2
Hyena 2 is thirsty
Gnu 1 is thirsty
A gnu enters the watercave         hyenas = 0         gnu = 3
Gnu 2 finished drinking and exits the watercave
Hyena 1 is thirsty
Hyena 3 is thirsty
Gnu 3 finished drinking and exits the watercave
Gnu 1 finished drinking and exits the watercave
A hyena enters the watercave       hyenas = 1       gnu = 0
A hyena enters the watercave       hyenas = 2       gnu = 0
A hyena enters the watercave       hyenas = 3       gnu = 0
Hyena 2 finished drinking and exits the watercave
Hyena 1 finished drinking and exits the watercave
Hyena 3 finished drinking and exits the watercave

``` 

## Using a function operator (functor, function object)

Create a class Gnu. Implement at least the following

```C++
Gnu::Gnu(int id) { ...           // constructor, id is the number of the Gnu
void Gnu::operator()()  { ....   // function operator - copy gnu function here
ostream & std::operator<<(ostream & os, const Gnu & g) { ...  // print the Gnu
```

Copy the code from _gnu_ function you wrote earlier into the function operator. Replace the calls  
to the unordered_map and print the gnu object directly instead.

Use a function pointer to point to the function operator and
initialize the thread with the function pointer in your main program.

```C++

      Gnu g = Gnu(24);
      std::function<void(void)> threadjob = g;
      threadvec.push_back(thread(threadjob));

```

### Questions

#### What is [this] in the lambda function sent to the condition_variable's wait-method? Why is [this] needed?
`this` is a pointer to the WaterManager instance, and in this case allows the lambda to check how many gnus are inside.

#### Why is the lock a local variable? What happens when the variable goes out of scope?

Easier to manage scopes and avoid deadlocks. When the lock goes out of scope (it gets destroyed), the lock automatically releases.

#### What is the difference between [unique_lock](http://en.cppreference.com/w/cpp/thread/unique_lock) and [lock_guard](http://en.cppreference.com/w/cpp/thread/lock_guard)

A lock_guard locks the mutex automatically upon creation, and when the scope is left the mutex is automatically released.

A unique_lock can be created without it being locked, and can unlock at any point during its existence, and can transfer ownership from one instance to another.

#### Do the integers _hyenasInside_, _gnusInside_ need be [atomic](http://en.cppreference.com/w/cpp/atomic/atomic)?

Not really. Since we're using locks to access them the atomic variables are unnecessary, at least for their current purpose.

#### Describe how .wait and .notifyall() works. Is any call blocking, and what does blocking mean?

`wait` causes the current thread to block until, and wakes up when the condition variable is notified, and may loop until some condition is fulfilled, if specified.

`notifyall` unblocks all threads that are waiting for that condition variable.

Blocked means exactly that. A thread is stuck there, and generally put to sleep by the operating system. 

#### Write code that iterates over an unordered_map and prints each key and value

```c
for (auto item: map)
    std::cout << item.first << " " << item.second << std::endl;
```

#### When printing an unordered_map, why is the items not printed in the order they were inserted?

Well, it is after all an _unordered_ map. The elements are not stored in any specific order, but in buckets, so you essentially cannot get your items back in order. 

#### In what order would the items be printed if a map was used instead of an unordered_map?

Prints in descending order by the key values.

#### How did you implement turning on/off trace outputs? Compile time, runtime or both? Ellaborate over your decision

I used global variables that are set at compile time to control trace outputs. The primary reason I did was for laziness. For this specific purpose I saw no reason to write a complicated logger or pass booleans to functions and the gnu class. 

One proper alternative would be to write a logger class, and write a `get_logger` function that returns an ostream that you can write to, or pass strings. This is obviously more scalable because the logger can be retrieved from several source files. 

#### What information did you print out in your trace output from the watercave? Ellaborate over your decision

1. When a gnu is thirsty, this signalises that they want to enter
2. When a gnu actually enters, and then writing how many of each animals are inside the waterhole. In this manner I can see if there by mistake are animals of different species at the same time inside (which is bad).
3. When a hyena is thirsty. This signalises that they're in queue to get in, and the corresponding hyena thread is blocked.
4. When a gnu leaves + stats. We see that the number of gnus decrease, and when it hits 0 (last gnu leaves), hyenas start flooding in when their threads are unblocked. 
5. Hyenas leave + stats, we see after that when gnus enter. 

Basically the numbers in the stats are the most important, as well as the order of the prints. 

#### Do you prefer initializing your thread with a function or function object (functor)

function object. allows for more flexibility with regard to implementation.
