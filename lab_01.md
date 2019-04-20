# Lab 1

This section will focus on the basics of compiling source code. Please use the
literature associated with this course, as well as resources online to acquire
further information about the topics discussed.


If you are not familiar with git you may need to read up on git. There is KTH-specific guide (in swedish [here](https://www.kth.se/social/files/55f1b20ef276547bf8af78fc/git_draft.pdf). There are plenty of other resources on the internet on git, some can be found [here](https://help.github.com/articles/good-resources-for-learning-git-and-github/)

If you have not done so already, [follow these steps to generate ssh-keys](https://help.github.com/articles/generating-an-ssh-key/) but use _gits-15.sys.kth.se_ instead of _github.com_ and perhaps do use ordinary copy/paste instead of _clip < ~/.ssh/id_rsa.pub_

Pull code from your assigned empty git repository. If you have generated ssh-keys you should be able to run something similar to this on your command line:
```
git clone git@gits-15.sys.kth.se:cprogYEAR/YOUR-KTH-LOGIN-labbar.git
```

Change your working directory to the root of your cloned git repository. Do not edit any files in the root directory. Change working directory once more to _01_ and do all your work for this assignment in _01_.

```
> cd path/to/cloned-repository
> cd 01
```


## How do I compile my implementation?

This course will use _g++_ to compile source code into object files, as
well as linking them to produce a final executable. The current version on school ubuntu is _5.4.0_

Create a file *hello_world.cpp* in 01 with the following content
```C++
#include <iostream>

int main () {
  std::cout << "Hello, World!\n";
}
```

Look at the file content with the more command (*more* works on linux, OS X and Windows, there is a similar command *cat* that does not work on Windows.)

```C++
> more hello_world.cpp
#include <iostream>
int main () {
    std::cout << "Hello, world!\n";
}
```

To compile the source code, and thereby produce an executable we may
invoke _g++_ in the manner stated below:


```
> g++ -o say_hello.out hello_world.cpp
> ./say_hello.out
```
where we first compile the source code and then run it.

If there are any problems during compilation, such as trying to
compile an ill-formed program, _g++_ will print diagnostics related to
such, and no executable will be created.

## building with make

For larger projects it is recommended to use a build system. One such system is
called _make_ which is what we will use throughout this
course.

_make_ will read the contents of a file named _makefile_ in the
current working directory. This file contains rules specifying
how to build parts of your project, or simply put; how to produce an executable.

Create a file named *makefile* with the following content. 

```
%.out: %.cpp
       g++ -std=c++11 -g -Wall $*.cpp -o $*.out
```

```
> more makefile
%.out: %.cpp
       g++ -std=c++11 -g -Wall $*.cpp -o $*.out
```

Instead of messing around with a rather complex invocation of _g++_, you
can now produce an executable named _hello\_world.out_, compiled from a
source file named _hello\_world.cpp_, by simply invoking _make
hello\_world_.

```
    > make hello_world.out
    > ./hello_world.out
    Hello, world!
```

#### g++ compiler questions

#### Where can you find the manual to g++?

####  What is the purpose of _-Wall_ and _-g_, when passed as arguments to _g++_?

####  How can you store the previous mentioned flags in a variable in the makefile?

#### Find and write down 4 other arguments tp _g++_ that you think might be useful and write a short motivation why you selected these specific 4 arguments.

#### What is the difference between an object file, and an executable?

Rewrite your current *makefile*  with the following content. Save. 

```
CC    = g++

FLAGS = -std=c++11 -g -Wall -pedantic

main.out: main.cpp hello.o
	 $(CC) $(FLAGS) main.cpp hello.o -o main.out

hello.o: hello.cpp
	$(CC) $(FLAGS) -c hello.cpp

clean:
	rm -f *.o *.out

```

### using git

Check the git status

```
> git status
Ändringar ej i incheckningskön:
(använd "git add <fil>..." för att uppdatera vad som skall checkas in)
(använd "git checkout -- <fil>..." för att förkasta ändringar i arbetskatalogen)

      ändrad:        makefile
```

Commit the new version of the _makefile_ to git. First you need to add it to the commit queue before commiting.

```
> git add makefile
> git commit makefile -m "changed makefile"
[master 3a939d5] changed makefile
 1 file changed, 13 insertions(+), 2 deletions(-)
```

*Note: You can edit and commit files directly in the web interface as well but then you need to synchronize your local repository*

Look at the content of _makefile_ by invoking _more makefile_

```
> more makefile
CC    = g++
#CC   = clang++-3.8 -L /usr/lib/gcc/x86_64-linux-gnu/5.4.0 -I /usr/include/x86_64-linux-gnu/c++/5.4.0 -I /usr/include/c++/5.4.0

FLAGS = -std=c++11 -g -Wall -pedantic

main.out: main.cpp hello.o
	 $(CC) $(FLAGS) main.cpp hello.o -o main.out

hello.o: hello.cpp
	$(CC) $(FLAGS) -c hello.cpp

clean:
	rm -f *.o *.out

```

The old version of the makefile can be viewed with _git show_

```
git show HEAD~:01/makefile
%.out: %.cpp
       g++ -std=c++0x -g -Wall $*.cpp -o $*.out
```

#### Git Questions

#### What does _git show HEAD~:01/makefile_ show?

#### What does _git show HEAD:01/makefile_ show?

#### What would _git show HEAD~~:01/makefile_ show?

#### What does the _~_ in the previous _git show_ commands mean?

#### Why can you not ommit _01_ in the previous commands (i.e. _git show HEAD~:makefile_ instead of  _git show HEAD~:01/makefile_)

#### Sometimes you may need to do a _git pull_ before you can do a _git push_ how can that be?

#### What is the purpose of the .git_ignore file and why should \*.o \*.out \*.exe be in this file when developing C++?


## How _make_ works

Copy the following files.

* [hello.cpp](01/hello.cpp)
* [hello.h](01/hello.h)
* [main.cpp](01/main.cpp) 


invoke _make_ to see the
resulting behavior. Try to build the executable two times without making any
changes to the dependent files.

```
    > make
    g++ -std=c++11 -g -Wall -pedantic -c hello.cpp
    g++ -std=c++11 -g -Wall -pedantic main.cpp hello.o -o main.out
    > make
    make: `main.out' is up to date.
```

Upon invoking _make_, the program will look for _dependencies_ that
are more recently modified than the _target file_. If there are no such
file, and a target file is already present, _make_ will decide that
there is nothing to do; why work for something that has already been done?


_touch_ can be used to change the modification timestamp of a file to
the current time (effectively making it look _as if_ the file has been
modified).

Change the modification timestamp of _main.cpp_ by invoking _touch_.

```
> touch main.cpp
```

Now invoke _make_, and notice that _hello.cpp_ will not be recompiled.

```
> make
g++ -std=c++11 -g -Wall -pedantic main.cpp hello.o -o main.out
```

#### makefile questions

#### If you invoke _touch hello.cpp_ prior to invoking _make_, how many files were rebuilt?

#### Why?

#### Why do you think _make_ checks the modification timestamp of the relevant files as part of deciding what to do?

#### What is the difference between an implicit rule and an explicit rule in a makefile?

#### What does _\$*_ mean inside a _makefile_?

## clang compiler

There is an alternative compiler (_clang_) installed on the school ubuntu
systems. To switch from using _gcc_ to _clang_, modify the
_makefile_ and set CC uncomment the following line (by removing _\#_).

```
#CC   = clang++-3.8 -L /usr/lib/gcc/x86_64-linux-gnu/5.4.0 -I /usr/include/x86_64-linux-gnu/c++/5.4.0 -I /usr/include/c++/5.4.0
```

On school ubuntu machines you use _module add clang_ which will set
library- and include-paths and also set _clang++_ as alias to clang++-3.8

Using a different compiler can often allow you to view potential errors from a
different angle (mostly because different compilers present errors in different
ways), making it easier to realize what went wrong, and more importantly; why.

Build and run the program using _clang_ instead of _g++_.

## Assignment an improved world of hello

_hello, world_ is a classic program that dates back to 1974, first published
in a paper titled _Programming in C: A tutorial_. The program has one
simple purpose; to print "_hello, world_".

Since the typical implementation is trivial, your task is to write a more
versatile alternative, having the following semantics:

```
> ./hello
Hello, world!
> ./hello "DD1387"
Hello, DD1387!
> ./hello "KTH" 3
Hello, KTH KTH KTH!
> ./hello "KTH" 0
> ./hello "KTH" 2
Hello, KTH KTH!
> ./hello "Malcom X" NaN
error: 2nd argument must be an integral greater than zero!
> ./hello kth dd1387 3
```

_This assignment is not an exercise in object oriented programming (OOP), but
a mere introduction to the fundamental parts of C/C++_

### Requirements

* _main.cpp_ contains the definition of the applications _main_-function.
There is no need for you to modify this file, but please make sure that
you understand what is written in it.

* _hello.cpp_ has a corresponding _.h_-header that contains
_forward-declarations_ for the functions you are to implement.

* This header, _hello.h_, is included (_#include_) by
_main.cpp_, and should be included by _hello.cpp_.

* _hello.cpp_ shall be compiled separately, resulting in an
object file that is to be linked into the resulting executable.

* You shall implement a function named _parse\_args_ in a separate
_translation unit_ named _hello.cpp_.
This function is responsible for parsing/interpreting the command line
arguments passed to the application, and shall return a
[_std::pair_](http://en.cppreference.com/w/cpp/utility/pair)
with what to print, and how many times to print it.

* _parse\_args_ shall handle all input errors by returning _-1_
as the second value of the returned _std::pair_, as well as printing
a suitable error message on _stderr_.

*    You shall implement a function named _hello_ in a separate
_translation unit_ named _hello.cpp_ (i.e. the same file that
shall contain the implementation of _parse_args_).

    _hello_ is responsible for printing the _hello world_-string on
_stdout_ with the following semantics;

    *     If the value _zero_ is passed as the second parameter,
    nothing shall be printed.

    * If a value greater than _zero_ is passed as the second argument
(_count_), _"Hello, "_ shall be printed followed by
_count_ space-delimited occurrences of the first argument.
The output shall end with an exclamation mark, followed by a new-line.
*Note_: hello ("KTH", 3)* shall print _Hello, KTH KTH KTH!_ (see the
  previous example invocations of the program for more information).

* Correct output from your program shall be printed through
_std::cout_, whereas potential error diagnostics (detected by
_parse\_args_) shall be printed through _std::cerr_.

* Your implementation, _hello.cpp_, [shall be uploaded to, and approved by, _Kattis_](https://kth.kattis.com/problems/kth.cprog.helloworld).

* Register on kattis by clicking the link [_I am a student taking this course and I want to register for it on Kattis_](https://kth.kattis.com/courses/DD1388/cprog18)

### Hints

* The argument named _argc_ to _main_ will contain the number of
arguments passed to your application. Remember that the name of the
executable counts to this number.

* The second argument, _argv_, will provide access to the individual
arguments passed to your application.

* _std::atoi_ from _<cstdlib>_ can be used to convert a
_char const *_ to an integer. If the function is unable to interpret
the data as an integer, it will return _0_.




#### Hello world questions

#### What is the purpose of _std::cout_, _std::cerr_, and _std::clog_, respectively?

#### How does #include work?

## Train Spotting (debugging)

Copy the file [_weird.cpp_](01/weird.cpp). Read through its source code and try
to reason about the runtime behavior of the program without running it.


```C++
#include <iostream>
#include <iomanip>

int powerof (int x, int y) {
  int res = 1;

  for (int i = 0; i < y; ++i);
    res = res * x;

  return res;
}

void adding_a_decimal(float step) {
  float sum = step;
  for (int i = 0; i < 1000*1000; ++i) {
    sum += step;
  }
  std::cout << std::setw(4) << sum << std::endl;
}

int main () {
  int const a = 2;
  int const b = 4;

  int   x = powerof(a, b);
  std::cout << a << "^" << b << " = " << x << ";\n";

  adding_a_decimal(0.1);

  float y;
  std::cout << "What is the value of PI? ";
  std::cin >> y;
  if (y == 3.1415)
    std::cout << y << " is equal to 3.1415!\n";
  else
    std::cout << y << " is not equal to 3.1415!\n";
}
```

Compile and execute the program.

```
> g++ -std=c++11 -g -Wall -pedantic weird.cpp -o weird.out
> echo '3.1415' | ./weird.out
```

Hopefully you notice how the behavior differs
from what one might expect. Your task is to figure out why that is with the
help of a debugger.

### Using a debugger

The accompanying debugger for gcc is called _gdb_. It uses a
command line interface.  There is a graphical user interface to gdb
called _ddd_ on the lab computers. If you use your own computer
there may be other debuggers available (lldb, visual studio, eclipse
etc). Feel free to google and install an alternative C++ debugger.

Use the debugger of your choice to identify why the program does not behave as
one might have anticipated.

#### debugging questions

#### Why does not _powerof_ return the expected value (_16_), when invoked with _2_ and _4_?

#### Why does not _adding_a_decimal_ output 100000?

#### Describe how _weird.out_ is invoked by _echo '3.1415' | ./weird.out_  

#### Why does not _y_ compare equal to _3.1415_?

#### Is there any difference in behavior if we compare _y_ to _3.1415f_, if so; why?

#### Describe and motivate the recommended method to use when trying to determine if two floating-point values are equal.


## unit testing

copy the files [_count_if_followed_by.cpp_](01/count_if_followed_by.cpp) 
and [_count_if_followed_by.h_](01/count_if_followed_by.h)

```
// .-------------------------------------------------------
// |        count_if_followed_by (data, len, a, b);
// |
// | About: Returns the number of occurances of
// |        a followed by b in the range [data, data+len).
// '-------------------------------------------------------

int count_if_followed_by (char const * p, int len, char a, char b) {
  int        count = 0;
  char const * end = p + len;

  while (p != end) {
    if (*p == a && *(p+1) == b)
      count += 1;

    ++p;
  }

  return count;
}
```

### _cxxtest_ a unit test framework

A unit test framework, such as (_cxxtest_)[http://cxxtest.com/], allows a
developer to specify constraints, and the expected behavior, of an
implementation that he/she would like to test.

These rules are later used to generate _unit tests_. These unit
tests will test to see that an implementation behaves as it shall (according to
the previously stated specification).

The steps associated with using a unit test framework for C++ typically
includes the following:

* Specify the constraints and requirements that you would like to test.

* Ask the unit test framework to generate a _test runner_ having
semantics associated with your specifications.

* Compile the _test runner_ into an executable.

* Invoke the executable to commence testing.

### Generating a _test runner_

Copy the file [_simple.cxxtest.cpp_](01/simple.cxxtest.cpp)

Asking _cxxtest_ to generate a _test runner_ from the contents of this
file can be accomplished through the following:

```
> /info/DD2387/labs/cxxtest/cxxtestgen.py --error-printer -o simple_testrunner.cpp simple.cxxtest.cpp
```

or by invoking python directly

```
> python /info/DD2387/labs/cxxtest/cxxtestgen.py --error-printer -o simple_testrunner.cpp simple.cxxtest.cpp
```

Before we can execute our _test runner_, the _test runner_ itself must
be compiled it into an executable. This includes linking it together with an
object file that contains our implementation.

Create an object file of our implementation:

```
> g++ -c -o count_if_followed_by.o count_if_followed_by.cpp
```

Compile our _test runner_, and link it with the object file:

```
> g++ -o simple_test.out -I /info/DD2387/labs/cxxtest/ \
  simple_testrunner.cpp count_if_followed_by.o
```

The test can be run by invoking _./simple_test.out_.

### Writing a test using _cxxtest_

*Note_: You may simplify the task of generating, and compiling,
test runners by writing a new rule inside your _makefile*

There is an intentional bug in the definition of
_count_if_followed_by_; it will potentially access one element outside
the range specified.  Collectively, bugs of this sort is most often referred to
as "_off-by-one errors_".

```C++
// expected: result == 0
//  outcome: result == 1 (!!!)

char const data[4] = {'G','G','X','G'};
int  const result  = count_if_followed_by (data, 3, 'X', 'G');
```

### Requirements

* Implement three (3) different tests that test the correct, and incorrect,
behavior of _count_if_followed_by_. The tests shall be presented
during your oral presentation, so make sure that you have them available
when it is time for such.

#### unit test questions

#### Why is it important to test the boundary conditions of an implementation, especially in the case of _count_if_followed_by_?

#### Describe how the testcase tests if a pointer is accessing an element outside the range specified


## Will It Float? (temporaries, resource management, valgrind)

There is a source file named _complex.cpp_. It is recommended to use a debugger,
or to add print-statements in the
source code, to make it easier to reason about its runtime behavior.

#### class construction questions

#### What constructors are invoked, and when? List the corresponding lines and name the invoked constructor

#### Will there be any temporaries created, if so; when?

#### What will happen if we try to free a dynamically allocated array through _delete p_, instead of _delete [] p_?


## _valgrind_ a memory management analyzer

Copy the file [_complex.cpp_](01/complex.cpp)

Compile _complex.cpp_ and run valgrind on the executable

```
> g++ -pedantic -Wall -std=c++11 -g complex.cpp -o complex.out
> valgrind --tool=memcheck --leak-check=yes ./complex.out
```
### valgrind

#### _valgrind_ indicates that there is something wrong with _complex.cpp_; what, and why?

Create a file called _bad_plumming.cpp_ with the following content

```C++
struct Data {
    int x, y, z;
};  

Data ** foo(Data ** v, int x) {
    for (int i = 0; i < x; i++)
        if (v[i] != 0)
            v[i] = new Data;
    return v;
}

int main () {
    const int size = 5;
    Data ** v = new Data * [size];
    foo(v, size);
}
```

Compile this program, then run _valgrind_ to analyze the
correctness and behavior.

#### _valgrind_ indicates that the program suffers from a few problems, which and why?

#### If you comment out the entire if-block in _foo_, is there any difference in how much memory that is leaked?

Revert _bad_plumming.cpp_ to its original state, then only comment
out the line that contains the if-condition.

```C++
    for (int i = 0; i < x; i++)
        // if (v[i] != 0)
            v[i] = new Data;
```

Change the last line of _main_ to the below.

```C++
    Data ** p = foo(v, size);
    delete [] p;
```


#### Why is it that valgrind still issue diagnostics related to memory management?

### -fsanitize=leak

Revert _bad_plumming.cpp_ to its original state

Compile with the option -fsanitize=leak and run the program 

```
> g++ -g -fsanitize=leak bad_plumming.cpp
> ./a.out
```

#### Add code that fixes the memory management

## Oral and offline review

Write your answers to the questions above in [markdown-format](https://www.markdowntutorial.com/) in a file called inquiry.md 
Do copy relevant code to your answers so that both questions and answers are in context. Do not forget
to push _inquiry.md_ after answering a question.

### Good luck
