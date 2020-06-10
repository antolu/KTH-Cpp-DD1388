## Answers to questions

> Are there any benefits using template meta programming to calculate prime numberis in compile time compared to the program that generated C++ code for prime numbers?


> Can you caltulate and assign an array of prime numbers in compile time using constexpr?

an array, yes. however since we don't know how many prime numbers there are up to an integer N, we cannot dynamically set the size of the array to the number of generated primes. Since integeral types, one can "fulhacka" with a template with <int N>, and either have an array of booleans representing the indices that are primes, or creating a N sized array and only fill it up to the number of generated primes and set the rest to 0.

> Can the compiler evaluate if statements in compile time using constexpr?
Yes, as long as the resulting object is instantiated as constexpr. 

> What did you learn from this assignment?
The difference between constexpr and template metaprogramming. And also how crazy C++ is.