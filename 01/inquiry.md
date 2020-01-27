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

> What is a forward declaration?

Declaration of a variable or type before the usage, and tells the compiler what that type is. 

> Why is it not possible to have class A containing a B object and B containing an A object? 

`class A { B b; };`
`class B { A a; };`

Because A would have to be completely declared before declaration of B, and vice versa. Instead a pointer is used for one of the two member variables. 

> Why are include guards needed?

So that one header is not included more than one time during compilation. 

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
With an implicit rule the recipe is not explicitly stated, but is instead left to makefile to decide (usually the common `g++ file.cpp -o file.o` is used), contrary to an explicit rule when dependency and command should be explicitly written. 

> What does $* mean inside a makefile?
The stem with which an implicit rule matches. The stem is useful for constructing names of related files.

### Hello World questions

> What is the purpose of _std::cout_, _std::cerr_, and _std::clog_, respectively?
* `std::cout`: writes information to the default output stream.
* `std::cerr`: writes information to the default error stream.
* `std::clog`: writes information to the default error stream, but is not automatically flushed. 

> How does #include work?
Includes the contents of the argument at that location in the code. 

