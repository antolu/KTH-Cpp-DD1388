> What is the benefit of having a conversion constructor?

Allows for implicit conversion from the type in the argument to the class type.
eg. `Complex x = 1` creates a complex number `1+0i` as expected

> Which of your class methods or non member functions returns a copy?

The binary non-chainable arithmetic operators, the literal operator `_i`, `abs`, `real`, `imag`. Basically any operation that returns a primitive type, except for the member functions that return the real and imaginary doubles.

> Which of your class methods or non member functions returns a reference?

Arithmetic operators `+=` etc, iostreams, assignment operator, and `real`, `imag`.

> How many tests do you need at minimum to test the abs function?
Four. There are 4 permutations of positive/negative numbers for a complex number.

> List some sample test cases (math operations) you have examined.

* 6+2i + 0+0i = 6+2i
* 6+2i - (5-3i) = 1+5i
* (6+2i) * (5-3i) = 36-8i
* (6+2i) / (5-3i) = 36/34 - 8/34i

> Were there any constructor calls in the above list that surprised you?

Not really.

> Describe and motivate how your implementation of operator= works
Create a new Complex object using the real and imaginary number variables in from the other Complex object. The values of the doubles are copied, and not their memory adresses.

> What constructors/functions are called when writing the statement Complex k = 3 + 5_i;

The literal operator ""_i (overloaded for integral numbers), and the copy-constructor Complex(double real).
So the ltieral operators makes 5_i a Complex, and the conversion operator is implicitly invoked on the 3. 

> Describe and motivate how your implementation of operator+= -= /= *= works

I want the operators to be chainable, so they return a reference to the lhs object, modified with the corresponding arithmetic operation. Otherwise they are the same as the normal arithmetic operators. 

> What is the rule of three in C++. Look it up in the course book or on the web.
The rule of three is a rule of thumb in C++ that claims if a class defines one (or more) of the folliwing, it should probably define all three:

* Destructor
* Copy constructor
* Copy assignment operator

Nowadays the rule of three has mostly been replaced by the rule of five, with the addition of a move constructur and a move assignment operator.

> Do you need to explicitly define and implement the copy-constructor in this assignement?

In this assignment, no. Should the member variables however be something like poiters or arrays, an explicit copy-constructor with deep-copying code is needed. In this case, the compiler generates a member-wise copying of the class.

> The literal i has an underscore before it. Why is that? Look it up in the c++11 draft section 17.6.4.3.5 and explain. Has there been any changes regarding this matter in the new c++17 draft

The suffixes that do not begin with an underscore are reserved for the standard library.

> What was the harderst part (or parts) in this assignment?

Understaning literal operators and constexpr.
