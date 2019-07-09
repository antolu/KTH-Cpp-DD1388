## g++ compiler questions

> Where can you find the manual to g++
`man g++` in the terminal, or [https://linux.die.net/man/1/g++](https://linux.die.net/man/1/g++)

> What is the purpose of _-Wall_ and _-g_, when passed as arguments to _g++_?

`-Wall` flag turns on all warnings the compiler can tell you about. `-g` flag adds debugging data to the executable?

> How can you store the previous mentioned flags in a variable in the makefile?
`CFLAGS = -Wall -g` (just a "normal" variable)

> Find and write down 4 other arguments tp _g++_ that you think might be useful and write a short motivation why you selected these specific 4 arguments.

* `-I` include other path for headers. Very useful if not all headers are in the same directory. 
* `-shared` produces a shared library, useful for writing cross-language wrappers for example.
* `-l[library name]` dynamically links to the library. Quite useful for larger projects. 
* `-ggdb` provides gdb debugger info. 


> What is the difference between an object file, and an executable?

Executable contains machine code interpretable and directly runnable by the system, while the object file is compiled, but not yet completely translated into machine code. 

> What does git show HEAD~:01/Makefile show?  
Shows the previous (not current) commit of Makefile

> What does git show HEAD:01/Makefile show?  
Shows the latest commit of Makefile

> What would git show HEAD~~:01/makefile show?  
The "grandparent" of Makefile, should it exist (ie. 2 revisions back in time).  

> What does the ~ in the previous git show commands mean?  
The tilde operator makes git look at the parent of the specified commit (in the above cases, HEAD). 


> Why can you not omit 01 in the previous commands (i.e. git show HEAD~:makefile instead of git show HEAD~:01/makefile)  
Because Makefile is not in the root of the repository. One needs to specify the full path. 


> Sometimes you may need to do a git pull before you can do a git push how can that be?   
git pull = git fetch + git merge, so one needs to merge the last last remote commit into the current local one before pushing all changes. 

> What is the purpose of the .gitignore file and why should *.o *.out *.exe be in this file when developing C++?  
Makes `git` ignore the files in the file system. Useful for when compiling code into .o, .out, and .exe files and want git to ignore those "changes". Good way of keeping `git status` clean. Even better is to add `build` to .gitignore and compile out-of-source. 

> If you invoke touch hello.cpp prior to invoking make, how many files were rebuilt? Why?  
Two. main.cpp depends on hello.cpp, so if hello.cpp is modified, main.cpp has to be recompiled.
> Why do you think make checks the modification timestamp of the relevant files as part of deciding what to do?  
Say one replaced a variable of x characters with an equally long variable in terms of character length. The outcome of the code will likely be changed, even though the file size for instance has not been changed. Thus the timestamp of the file should matter.

> What is the difference between an implicit rule and an explicit rule in a makefile?  
Implicit rules leave make to figure out while files should be prerequisites and even tries to deduce the recipe, while explicit rules state precisely which files the rule depends on and how the destination file is created from dependencies.

> What does $* mean inside a makefile?

From GNU make: "The stem with which an implicit rule matches".

For instance from my makefile: 
```
%.out : %.cpp
	g++ -std=c++11 -g -Wall $*.cpp -o $*.out
```
So the $* variable "constructs" names of the relevant files. Ie foo.cpp is compiled to foo.out, where $* is foo (the stem), in this case. 

#### Hello world questions

> What is the purpose of `std::cout`, `std::cerr` and `std::clog`, respectively? 
* `std::cout` writes to the standard C output stream stdout. 
* `std::cerr` writes to the standard C error stream stderr, and is not buffered. 
* `std::clog` writes to the standard C error stream stderr, but does not flush it. Us clog for logging? 

> How does `#include` work?

#### Debugging questions

> Why does not `powerof` return the expected value (_16_), when invoked with _2_ and _4_?
The for-loop is terminated by a `;` and is not executed. 

> Why does not `adding_a_decimal` output 100000?
Floating point precision errors. When summing `sum += step` sum is not exactly incremented by a step, but also includes errors in floating point precision.

> Describe how `weird.out` is invoked by `echo '3.1415' | ./weird.out`  
Connects (pipes) the output of echo to the weird executable. Since weird has a `std::in` statement, the output of echo ("3.1415") is piped into the standard C input buffer stdin, and is read by the executable at std::cin. 

> Why does not `y` compare equal to `3.1415`?
`3.1415` is not of type float. 

> Is there any difference in behavior if we compare `y` to `3.1415f`, if so; why?
It's a question of rounding and precision. Double is doule precision while float is single precision, and the computer usually does not represent the numbers as exactly as one would like them to be. For instance `3.1415` could in fact be `3.14150000000000000000000038791`. So if comparing two different decimal numbers they likely will not be the same. 

> Describe and motivate the recommended method to use when trying to determine if two floating-point values are equal.

As mentioned before, comparing two floats or doubles or float and double needs comparing the numerical valeus of the two. So the recommended method of doing so is simply

```
if ((floatA - floatB) < EPSILON )
    // Do something
```

And one has to choose a proper magnitude for epsilon. This way two numerical values are equal if the difference is smaller than a preset, and is the only way to accurately check if two single- or double-precision values are the same. 

> Why is it important to test the boundary conditions of an implementation, especially in the case of count_if_followed_by?

Boundary values are typically where an implementation needs double checking so the algorithm does precisely what it's supposed to do. 

> Describe how the testcase tests if a pointer is accessing an element outside the range specified

When the pointer accesses an element outside of the range specified, it accesses memory not belongning to the array. Thus it can yield very strange results.



### Will It Float? (temporaries, resource management, valgrind)

> What constructors are invoked, and when? List the corresponding lines and name the invoked constructor
First constructor (some other constructor), explicit initialisation,
Second constructor (copy-constructor), implicit assignment
Third constructor (copy-constructor), copy initialisation
Forth constructor (default constructor), default initialisation

> Will there be any temporaries created, if so; when?


> What will happen if we try to free a dynamically allocated array through delete p, instead of delete [] p?
Segfault. 
