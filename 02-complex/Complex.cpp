#include "Complex.hpp"
#include <cmath>

Complex::Complex() {
  r = i = 0;
}

Complex::Complex(double real) : Complex::Complex(real, 0) {}

Complex::Complex(const Complex& other) {
  r = other.r; i = other.i;
}

Complex& Complex::operator=( const Complex &other ) {
  r = other.r; i = other.i;

  return *this;
}

double& Complex::real() {
  return r;
}

double& Complex::imag() {
  return i;
}

Complex& Complex::operator+=( const Complex &other ) {
  r += other.r;
  i += other.i;
  return *this;
}

Complex& Complex::operator-=( const Complex &other ) {
  r -= other.r;
  i -= other.i;
  return *this;
}

Complex& Complex::operator*=( const Complex &other ) {
  double new_r = r * other.r - i * other.i;
  i = r * other.i + i * other.r; r = new_r;
  return *this;
}

Complex& Complex::operator/=( const Complex &other ) {
  double new_r = r * other.r - i * other.i;
  i = r * other.i + i * other.r; r = new_r;

  double denom = std::pow(abs(other), 2);

  r /= denom;
  i /= denom;
  return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
  return Complex(lhs.r + rhs.r, lhs.i + rhs.i);
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
  return Complex(lhs.r - rhs.r, lhs.i - rhs.i);
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
  return Complex(lhs.r * rhs.r - lhs.i * rhs.i, lhs.r * rhs.i + lhs.i * rhs.r);
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
  Complex num = lhs * rhs;
  double denom = std::pow(abs(rhs), 2);
  
  num.r /= denom;
  num.i /= denom;
  
  return num;
}

bool operator==(const Complex& lhs, const Complex& rhs) {
  return lhs.r == rhs.r && lhs.i == rhs.i;
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
  return lhs.r != rhs.r || lhs.i != rhs.i;
}

double abs(const Complex& c) {
  return std::sqrt( std::pow(c.r, 2) + std::pow(c.i, 2));
}

double real(const Complex& c) {
  return c.r;
}

double imag(const Complex& c) {
  return c.i;
}

std::ostream& operator<<(std::ostream& out, const Complex& c) {
  if (c.r == 0.0 && c.i == 0.0)
    out << "0";
  else if (c.r == 0.0)
    out << c.i << "i";
  else if (c.i == 0.0)
    out << c.r;
  else
    c.i > 0 ? out << c.r << "+" << c.i << "i" : out << c.r << c.i << "i";
  return out;
}

std::istream& operator>>(std::istream& in, const Complex& c) {
  (void) c;
  return in;
}

// constexpr Complex operator"" _i(long double arg) {
//   return Complex{0.0, static_cast<double>(arg)};
// }

