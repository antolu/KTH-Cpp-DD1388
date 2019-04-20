# Template meta programming prime numbers in compile time and n-dimensional matrices

## prime numbers

Write a function/method *find_primes(int N)* that given an int N
calculates all prime numbers up to N using the [sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).

### Basic algorithm

Begin by assigning a vector one or more prime numbers from 2 and
upwards. Iterate from 2 or your highest prime number to N. In each
iteration, do an inner loop that checks if the number is divisible
with your current known prime numbers, in which case it is not a prime
number. The inner loop needs only check divisibility up to the square
root of the number.

## generate hard coded prime numbers

Write a function/method *hard_coded_primes* that returns a *string* of
c++ code that initializes a *vector* with prime numbers.

```c++
  std::string s = hard_coded_primes();
  cout << s << endl;
  // prints
  // vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
```

Use stringstream to build your output string. You are free to choose
parameters. You may write functions or member functions in a class.

## Meta programming

The following program calculates the factorial for 5 in compile time. The compiler will recursively
generate code until the template specialization for _struct Factorial<1>_

```c++
template <int x>
struct Factorial
{
  static const int nr = x * Factorial<x - 1>::nr;
};

template <>
struct Factorial<1>
{
  static const int nr = 1;
};
int main()
{
  std::cout << Factorial<5>::nr << std::endl;
}
```

## Calculate prime numbers using template meta programming

Write template functions/structs that calculates prime numbers in compile time.

```c++
template <unsigned int X> struct
is_prime
{
  //...
};
```

Let the function call a helper template struct *check_if_prime*
which takes two template parameters and recursively checks
divisibility. Keep the first template parameter constant and count
down the second paramater.

```c++
template <int p, int i> struct check_if_prime
{
	// ...
};
```


#### Are there any benefits using template meta programming to calculate prime numbers in compile time compared to the program that generated c++ code for prime numbers?


## Using constepxr for compile time programming

Template meta programming is Turing complete but was not an intended design of C++. In the new standard C++17 compile time programming has been further improved using **constexpr**. Do read on C++17 standard. 

#### Can you calculate and assign an array of prime numbers in compile time using **constexpr** ?

#### Can the compiler evaluate if-statements in compile time using **constexpr** ?


## The N-dimensional matrix.

Implement an N-dimensional matrix using template meta programming.

```c++
NdimMatrix<3> n(9); // a cube with 9 * 9 * 9 elements
NdimMatrix<6> m(5); // a matrix in six dimensions with 5 * 5 * 5 * 5 * 5 * 5 elements
m[1][3][2][1][4][0] = 7;
NdimMatrix<3> t(5);
t = m[1][3][2];      // assign part (slice) of m to t, the dimensions and element size matches
t[1][4][0] = 2;      // changes t but not m
std::cout << m[1][3][2][1][4][0] << std::endl; // 7
std::cout << t[1][4][0] << std::endl;          // 2
```

Let **NdimMatrix** inherit from std::vector **or** have a std::vector as a member. When you have implemented the N-dimensional matrix, try to make the code more clean. It is possible to implemment *NdimMatrix* using only 10-15 lines of code. The operator[] should work as expected.

#### What did you learn from this assignment?
