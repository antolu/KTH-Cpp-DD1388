# Lab 2: Complex numbers


For this lab you will create a class that represents a complex number. In essence, you will create a class that can handle addition, subtraction, multiplication and division. Do investigate what constructors are called and be ready to answer sample questions of some math operations during oral exam.
How to do this can be found out by reading the [wikipedia page](https://en.wikipedia.org/wiki/Complex_number). You may refresh [conjugate algebra](https://en.wikipedia.org/wiki/Conjugate_%28algebra%29) when implementing division. You can also reference how the [standard library](http://en.cppreference.com/w/cpp/numeric/complex) implementation works. You will need to use -std=c++11 for this assignment.


## Functions
In the style of [cppreference](http://en.cppreference.com/w/cpp/numeric/complex) the following things should be defined:

| Member functions |  - |
|  ---                 | --- |
| (constructor)        | constructs a complex number (see guidance below) |
| `operator=`            | assigns the contents |
| `real`                 | accesses the real part of the complex number |
| `imag`                 | accesses the imaginary part of the complex number |
| `operator+=` `-=` `/=` `*=`  | compound assignment of two complex numbers or a complex and a scalar |



| Non-member functions  | - |
| ---             | ---|
| `operator+` `-`     | applies unary operators to complex numbers |
| `operator+` `-` `*` `/` | performs complex number arithmetics on two complex values or a complex and a scalar |
| `operator==` `!=`   | compares two complex numbers or a complex and a scalar |
| `real`            | returns the real component |
| `imag`            | returns the imaginary component |
| `abs`             | returns the magnitude of a complex number |
| `operator<<`           |  Writes to output stream the complex number in the form _(real,imaginary)_ |
| `operator>>`           | Reads a complex number from is. The supported formats are real, (real) and (real,imaginary) Where the input must be convertible to Double |
| `operator""_i`    | Forms a complex literal representing an imaginary number (note the underscore) |

## Specific Requirements

These following requirements need to be fulfilled to pass this lab.

* You have to write your own tests that verify that everything works. We will look very closely on these tests and they are expected to cover every unique possible scenario, better write too many than too few.

* Write a makefile where
  * _make all_ builds your class and testprogram
  * _make tests_ runs your tests

* The type that you use to save the values should be doubles.

* You should be able to answer what function/functions will be called for all types of assignments and constructions. Feel free to experiment with trace outputs (prints) in the functions to learn what is called. Remove, comment or use your preprocessor flags to hide your trace outputs in the final submission.

## Guidance
These are the constructor signatures that you will need:

* Complex();
* Complex(double real);     // _Note: [non explicit](http://en.cppreference.com/w/cpp/language/converting_constructor)_
* Complex(double real, double imaginary);
* Complex(const Complex &rhs);

This thing enables you to write complex numbers in literal form.
* constexpr Complex operator""_i(long double arg);

### Make your own design decisions

operator+= -= /= *=

You need to think about how operator= and operator+= -= /= *= should
work. The design decision is up to you Given _Complex x; Complex y;_
should all of these work or only a few? Make your own design decisions
and *motivate* them.

* Complex x; Complex y;
* x = y + 1;
* x = y + y + 1 + 5;     // chaining
* x = 2 + y;
* x += y += 4;           // chaining

## Basic test examples

Examples of things that should work. Note you must test more extensively on your own.

* Complex x;
* Complex x2 = 5;
* Complex y(6, 2);
* Complex z = x + y;
* Complex k = 3 + 5_i;
* k -= 5 + 1_i * Complex(5, 3);
* std::cout << Complex(6, 6) / 6 << std::endl;

## Questions

Put questions and answers in a file inquiry.md do put relevant code examples if needed for clarity.

#### What is the benefit of having a [conversion constructor](http://en.cppreference.com/w/cpp/language/converting_constructor)?

#### Which of your class methods or non member functions returns a copy?

#### Which of your class methods or non member functions returns a reference?

#### How many tests do you need at minimum to test the _abs_ function?

#### List some sample test cases (math operations) you have examined.

#### Were there any constructor calls in the above list that surprised you?

#### Describe and motivate how your implementation of operator= works

#### What constructors/functions are called when writing the statement Complex k = 3 + 5_i;

#### Describe and motivate how your implementation of operator+= -= /= *= works

#### What is the rule of three in C++. Look it up in the course book or on the web.

#### Do you need to explicitly define and implement the copy-constructor in this assignement?

#### The literal _i_ has an underscore before it. Why is that? Look it up in the [c++11 draft](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3376.pdf) section 17.6.4.3.5 and explain. Has there been any changes regarding this matter in the [new c++17 draft](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4659.pdf)


#### What was the harderst part (or parts) in this assignment?
