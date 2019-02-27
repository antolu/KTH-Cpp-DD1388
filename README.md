# DD1388 Programsystemkonstruktion med C++

The assignments are to be solved individually. Make your changes in the for each
assignment corresponding subdirectories 01, 02 etc.
Every assignment requires an oral presentation where you shall be able to explain
and answer questions regarding your solutions.

If an assignment requires one or several written answers, a file named
inquiry.md will be available in the
corresponding _lab directory_ (01, 02, 03 etc). Use the file as a template for
submitting your answers. The file format is [markdown](https://en.wikipedia.org/wiki/Markdown).
A tutorial on markdown can be found [here](http://www.markdowntutorial.com/).

Your implementations is your means to prove that you fully understand important
C++ concepts such as references, virtual, pointers, const, template programming, memory
management which are taught during the course.  

* [Lab1](lab_01.md)

## General Requirements

* Your code should be modularized in classes and files.

* Make sure that your implementations is easy to read, maintain, and understand.
This includes the usage of correct indentation, as well as having suitable names
for your variables.

* Your implementations must not leak memory, or any other acquired resource.
Pay attention to the purpose of constructors, and their relationship with the corresponding destructor: Resource Acquisition Is Initialization

* Your implementations should demonstrate that you fully understand the semantics
associated with the keyword const

* Questions that require a written answer should be answered in an elaborate manner; single word answers will not be accepted. Each answer must consist of
at least one (1) full sentence.

* You are responsible for testing your lab assignments! Submit your test suites in git. Untested code may fail examination.


## Receipt

* Download and print the lab report receipt found at the course overview for DD1387 at the course web

* Fill out the lab report receipt.

* Remember to ask for a signature after each oral presentation associated with a particular lab.

* All results are reported to [rapp](http://rapp.csc.kth.se), and you are
    advised to check so that your results have been reported correctly. If results
    are missing in rapp you must contact the course leader and
    present your signed report receipt.

## Kattis

Some assignments require you to submit code for automatic testing, which will
verify that your implementation is correct in relation to the requirements set
forth by the assignment in question.

To submit an implementation for automatic testing, open up a web browser and
point it to [kth.kattis.com](https://kth.kattis.com), then;


*  authenticate using your KTH-id, if this is the first time you are using
    _Kattis_ you must register for the service after signing in, also;


*  make sure that you register as a student taking cprog16, before you try to
    submit any of your solutions.


## Git

If you are not familiar with git you may need to read up on git. There is KTH-specific guide (in swedish [here](https://www.kth.se/social/files/55f1b20ef276547bf8af78fc/git_draft.pdf). There are plenty of other resources on the internet on git, some can be found [here](https://help.github.com/articles/good-resources-for-learning-git-and-github/)
A tutorial for linux users is [here](http://www.tutorialspoint.com/git/git_quick_guide.htm)

You need, at minimum, to use _git status, git add, git commit, git push and git pull_.

If you have not done so already, [follow these steps to generate ssh-keys](https://help.github.com/articles/generating-an-ssh-key/) but use _gits-15.sys.kth.se_ instead of _github.com_ and perhaps do use ordinary copy/paste instead of _clip < ~/.ssh/id_rsa.pub_

Do not make any changes in the root directory. Do your changes in the subdirectories 01, 02, 03 etc. New material will be pushed to your repository during the course and you will need use _git pull_ to synchronize your local repository. Material will only be pushed to the root directory which, if untouched, will synchronize without conflicts.

### Good luck
