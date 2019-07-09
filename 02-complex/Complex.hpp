#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
 private:
  double r;
  double i;

 public:
  Complex();
  Complex(double real);
  Complex(double real, double imaginary);
  Complex(const Complex& rhs);

  void operator=(const Complex& other);

  double& real();
  double& imag();

  Complex& operator+=(const Complex& other);
  Complex& operator-=(const Complex& other);
  Complex& operator*=(const Complex& other);
  Complex& operator/=(const Complex& other);
  
  friend Complex operator+(const Complex& lhs, const Complex& rhs);
  friend Complex operator-(const Complex& lhs, const Complex& rhs);

  friend bool operator==(const Complex& lhs, const Complex& rhs);
  friend bool operator!=(const Complex& lhs, const Complex& rhs);

  friend double abs(const Complex& c);
  friend double real(const Complex& c);
  friend double imag(const Complex& c);

  friend std::ostream& operator<<(std::ostream& out, const Complex& c);
  friend std::istream& operator>>(std::istream& in, const Complex& c);
  friend constexpr Complex operator""_i(long double arg);
};

#endif
