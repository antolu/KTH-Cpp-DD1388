> What is the benefit of having a conversion constructor?
> Which of your class methods or non member functions returns a copy?
> Which of your class methods or non member functions returns a reference?
> How many tests do you need at minimum to test the abs function?
Four. There are 4 permutations of positive/negative numbers for a complex number. 

> List some sample test cases (math operations) you have examined.
> Were there any constructor calls in the above list that surprised you?
> Describe and motivate how your implementation of operator= works
Create a new Complex object using the real and imaginary number variables in from the other Complex object. The values of the doubles are copied, and not their memory adresses. 

> What constructors/functions are called when writing the statement Complex k = 3 + 5_i;
The literal operator ""_i (overloaded for integral numbers), and the copy-constructor Complex(double real). 

> Describe and motivate how your implementation of operator+= -= /= *= works
> What is the rule of three in C++. Look it up in the course book or on the web.
The rule of three is a rule of thumb in C++ that claims if a class defines one (or more) of the folliwing, it should probably define all three:
* Destructor
* Copy constructor
* Copy assignment operator

> Do you need to explicitly define and implement the copy-constructor in this assignement?
In this assignment, no. Should the member variables however be something like poiters or arrays, an explicit copy-constructor with deep-copying code is needed. In this case, the compiler generates a member-wise copying of the class. 

> The literal i has an underscore before it. Why is that? Look it up in the c++11 draft section 17.6.4.3.5 and explain. Has there been any changes regarding this matter in the new c++17 draft
> What was the harderst part (or parts) in this assignment?
Understaning literal operators and constexpr.
