## g++ compiler questions

### Where can you find the manual to g++

`man g++` in the terminal, or [https://linux.die.net/man/1/g++](https://linux.die.net/man/1/g++)

### What is the purpose of _-Wall_ and _-g_, when passed as arguments to _g++_?

`-Wall` flag turns on all warnings the compiler can tell you about. `-g` flag adds debugging data to the executable?

### How can you store the previous mentioned flags in a variable in the makefile?
`CFLAGS = -Wall -g` (just a "normal" variable)

### Find and write down 4 other arguments tp _g++_ that you think might be useful and write a short motivation why you selected these specific 4 arguments.

* `-I` include other path for headers. Very useful if not all headers are in the same directory. 
* `-shared` produces a shared library, useful for writing cross-language wrappers for example.
* `-l[library name]` dynamically links to the library. Quite useful for larger projects. 
* `-ggdb` provides gdb debugger info. 

### What is the difference between an object file, and an executable?

Executable contains machine code interpretable and directly runnable by the system, while the object file is compiled, but not yet completely translated into machine code. 

### What is a forward declaration?

Declaration of a variable or type before the usage, and tells the compiler what that type is. 

### Why is it not possible to have class A containing a B object and B containing an A object? 

`class A { B b; };`
`class B { A a; };`

Because A would have to be completely declared before declaration of B, and vice versa. Instead a pointer is used for one of the two member variables. 

### Why are include guards needed?

So that one header is not included more than one time during compilation. 

### What does git show HEAD~:01/Makefile show?  
Shows the previous (not current) commit of Makefile

### What does git show HEAD:01/Makefile show?  
Shows the latest commit of Makefile

### What would git show HEAD~~:01/makefile show?  
The "grandparent" of Makefile, should it exist (ie. 2 revisions back in time).  

### What does the ~ in the previous git show commands mean?  
The tilde operator makes git look at the parent of the specified commit (in the above cases, HEAD). 


### Why can you not omit 01 in the previous commands (i.e. git show HEAD~:makefile instead of git show HEAD~:01/makefile)  
Because Makefile is not in the root of the repository. One needs to specify the full path. 


### Sometimes you may need to do a git pull before you can do a git push how can that be?   
git pull = git fetch + git merge. If there are more changes on the remote that were committed between the last and current local commit, a merge between the remote and the local branch is required.

### What is the purpose of the .gitignore file and why should *.o *.out *.exe be in this file when developing C++?  
Makes `git` ignore the files in the file system. Useful for when compiling code into .o, .out, and .exe files and want git to ignore those "changes". Good way of keeping `git status` clean. Even better is to add `build` to .gitignore and compile out-of-source. 

### If you invoke touch hello.cpp prior to invoking make, how many files were rebuilt? Why?  
Two. main.cpp depends on hello.cpp, so if hello.cpp is modified, main.cpp has to be recompiled.

### Why do you think make checks the modification timestamp of the relevant files as part of deciding what to do?  
Say one replaced a variable of x characters with an equally long variable in terms of character length. The outcome of the code will likely be changed, even though the file size for instance has not been changed. Thus the timestamp of the file should matter.

### What is the difference between an implicit rule and an explicit rule in a makefile?
With an implicit rule the recipe is not explicitly stated, but is instead left to makefile to decide (usually the common `g++ file.cpp -o file.o` is used), contrary to an explicit rule when dependency and command should be explicitly written. 

### What does $* mean inside a makefile?
The stem with which an implicit rule matches. The stem is useful for constructing names of related files.

### Hello World questions

### What is the purpose of _std::cout_, _std::cerr_, and _std::clog_, respectively?
* `std::cout`: writes information to the default output stream.
* `std::cerr`: writes information to the default error stream.
* `std::clog`: writes information to the default error stream, but is not automatically flushed. 

### How does #include work?
Includes the contents of the argument at that location in the code. 

## Debugging questions

#### Why does not _powerof_ return the expected value (_16_), when invoked with _2_ and _4_?
```c++
for (int i = 0; i < y; ++i);
```

has a semicolon after the for loop, so the `res = res * x;` not in the for loop. 

#### Why does not _adding_a_decimal_ output 100000?
Floating point precision is not good enough. Switching the `sum` variable to `double` type largely remedies the problem.

#### Describe how _weird.out_ is invoked by _echo '3.1415' | ./weird.out_  
3.1415 is passed to the shell stdin, and then `weird.out` is executed, which in turn has a line that reads input from stdin, and reads 3.1415 into the `y` variable.

#### Why does not _y_ compare equal to _3.1415_?
By default, 3.1415 is of type `double`, so due to precision differences the values stored in memory will be different.

#### Is there any difference in behavior if we compare _y_ to _3.1415f_, if so; why?
The equality holds, because we are not comparing an exact float to an exact float.

#### Describe and motivate the recommended method to use when trying to determine if two floating-point values are equal.
Comparing the difference between two variables with a predefined epsilon threshold that's sufficiently small enough.
In other words

```c++
if (std::abs(a - b) < eps)
```

This is because a might be the same as b, but not down to the smallest decimals due to too low precision, so we need to compare them to an epsilon threshold that should be adapted to the application.

## Unit test questions

#### Why is it important to test the boundary conditions of an implementation, especially in the case of _count_if_followed_by_?
It's very common to have off-by-one mistakes, so we need to make sure we programmed the boundary condition correctly. For the `count_if_followed_by` example, see the next question.


#### Describe how the testcase tests if a pointer is accessing an element outside the range specified
It compares the current cursor `p` against the `p+len` pointer, so as long as the `p` value is not yet the end memory address, the loop continues. However the test case does not check if the `p+1` pointer is within range. In the case of the `test_len` being the size of the array, `p+1` will be outside the array.

### class construction questions

#### What constructors are invoked, and when? List the corresponding lines and name the invoked constructor

* `Complex a("3_2i");` calls the `Complex(char const* s)` constructor. This is a parametrized constructor.
* `Complex b = a;` calls the `Complex (Complex const& src)` copy constructor.
* `Complex c(a);` calls the same copy constructor.
* `Complex d;` calls the default constructor (without parameters).


#### Will there be any temporaries created, if so; when?
For the parametrized constructor, the argument `"3_2i"` is temporary rvalue reference.

#### What will happen if we try to free a dynamically allocated array through _delete p_, instead of _delete [] p_?
Only the destructor of the first element will be called. In essence not all memory is freed. 

## valgrind questions

#### _valgrind_ indicates that there is something wrong with _complex.cpp_; what, and why?
There is a memory leak, where at least 13 bytes were not freed after execution. In this specific example a dynamically allocated array was removed using the `delete` operator, as opposed to `delete[]`, so there are elements that were not destroyed, and thus causes a memory leak.

#### _valgrind_ indicates that the program suffers from a few problems, which and why?
`Conditional jump or move depends on uninitialised value(s)` as well as `40 bytes in 1 blocks are definitely lost in loss record 1 of 1`.
For the first, I noticed that the if statement comparing `v[i] != 0`, where `v[i]` has not been initialised, so we are comparing an uninitialised element against some literal, which may cause undefined behaviour. (although in this case it's fine because we are trying to compare an uninitialised element with an implicit nullptr)
For the second we see in `bad_plumbing` that the dynamically array was not deleted. So it remains in memory and causes a memory leak upon exit.

#### If you comment out the entire if-block in _foo_, is there any difference in how much memory that is leaked?
`100 (40 direct, 60 indirect) bytes in 1 blocks are definitely lost`, so more memory is lost.

#### Why is it that valgrind still issue diagnostics related to memory management?
`60 bytes in 5 blocks are definitely lost`, so we still lose memory.

