#include "Complex.hpp"

Complex::Complex() {
  r = i = 0;
}

Complex::Complex(double real) {
  r = real;
  i = 0;
}

Complex::Complex(double real, double imaginary) {
  r = real;
  i = imaginary;
}

Complex Complex::operator+( const Complex& other ) {
  Complex ret = Complex(this->real + other.real,this->img + other.img);
  return ret;
}

