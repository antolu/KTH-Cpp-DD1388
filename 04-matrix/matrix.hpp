#ifndef DD1388_MATRIX_HPP
#define DD1388_MATRIX_HPP

/**
 * Generic Matrix class
 *
 * Anton Lu
 * antolu@kth.se
 * KTH Royal Institute of Technology
 *
 * 2019-09-05
 *
 * Uses row major ordering in internal representation
 */


#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <type_traits>

template<class T>
class Matrix {

public:
  /* Constructors */
  Matrix<T>() : Matrix<T>(0) {}
  explicit Matrix<T>(unsigned size) : Matrix<T>(size, size) {}
  explicit Matrix<T>(unsigned rows, unsigned columns) {
    init(rows, columns);
  }
  
  Matrix<T>(std::initializer_list<T> list) {
    double size = std::sqrt(list.size());
    if ( !( (std::pow(std::round(size), 2) - list.size()) < 1e-8 ) )
      throw std::out_of_range("Initializer list size not a perfect square!");

    init(size, size);

    T* idx = m_vec;
    for (auto item: list) {
      *idx++ = item;
    }
  }
  
  ~Matrix() {
    if (m_vec == nullptr)
      return;
    delete[] m_vec;
    m_vec = nullptr;
  };

  /* Copy */
  Matrix<T>(const Matrix<T> &rhs) {
    copy(rhs);
  }
  
  Matrix<T>& operator=(const Matrix<T>& other) {
    /* if assigning to itself, do nothing */
    if (&other == this)
      return *this;

    if (m_vec) {
      delete[] m_vec;
      m_vec = nullptr;
    }
    copy(other);

    return *this;
  }

  /* Move */
  Matrix<T>(Matrix<T> &&other) {
    move(std::move(other));
  }
  
  Matrix<T>& operator=(Matrix<T> &&other) {
    move(std::move(other));
    return *this;
  }

  // operators
  T& operator() (unsigned row, unsigned column) {
    if (row * m_cols + column >= m_capacity || row >= m_rows || column >= m_cols)
      throw std::out_of_range("Accessing element out of range");
    return m_vec[row * m_cols + column];
  }
  
  const T& operator() (unsigned row, unsigned column) const {
    if (row * m_cols + column >= m_capacity || row >= m_rows || column >= m_cols)
      throw std::out_of_range("Accessing element out of range");
    return m_vec[row * m_cols + column];
  }

  friend Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    if (lhs.m_rows != rhs.m_rows || lhs.m_cols != rhs.m_cols)
      throw std::out_of_range("Dimensions do not match!");

    Matrix<T> ret(lhs.m_rows, lhs.m_cols);

    for (size_t i = 0; i < ret.m_capacity; i++)
      ret.m_vec[i] = lhs.m_vec[i] + rhs.m_vec[i];

    return ret;
  }

  friend Matrix<T> operator+(const Matrix<T> &lhs, const T &rhs) {

    Matrix<T> ret(lhs.m_rows, lhs.m_cols);

    for (size_t i = 0; i < ret.m_capacity; i++)
      ret.m_vec[i] = lhs.m_vec[i] + rhs;

    return ret;
  }

  friend Matrix<T> operator+(const T &lhs, const Matrix<T> &rhs) {
    return rhs + lhs;
  }
  
  friend Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    if (lhs.m_rows != rhs.m_rows || lhs.m_cols != rhs.m_cols)
      throw std::out_of_range("Dimensions do not match!");

    Matrix<T> ret(lhs.m_rows, lhs.m_cols);

    for (size_t i = 0; i < ret.m_capacity; i++)
      ret.m_vec[i] = lhs.m_vec[i] - rhs.m_vec[i];

    return ret;
  }

  friend Matrix<T> operator-(const Matrix<T> &lhs, const T &rhs) {

    Matrix<T> ret(lhs.m_rows, lhs.m_cols);

    for (size_t i = 0; i < ret.m_capacity; i++)
      ret.m_vec[i] = lhs.m_vec[i] - rhs;

    return ret;
  }

  friend Matrix<T> operator-(const T &lhs, const Matrix<T> &rhs) {

    Matrix<T> ret(rhs.m_rows, rhs.m_cols);

    for (size_t i = 0; i < ret.m_capacity; i++)
      ret.m_vec[i] = lhs - rhs.m_vec[i];

    return ret;
  }
  
  friend Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    if (lhs.m_cols != rhs.m_rows)
      throw std::out_of_range("Dimensions do not match!");

    Matrix<T> ret(lhs.m_rows, rhs.m_cols);

    /* a(i, j) = a.m_vec[i * n + j] */
    for (size_t i = 0; i < lhs.m_rows; i++)
      for (size_t j = 0; j < rhs.m_cols; j++)
	for (size_t k = 0; k< rhs.m_rows; k++)
	  ret.m_vec[i * ret.m_cols + j] += lhs.m_vec[i * lhs.m_cols + k] * rhs.m_vec[k * rhs.m_cols + j];

    return ret;
  }

private:
    size_t m_rows = 0;
    size_t m_cols = 0;
    size_t m_capacity = 0;
    T *m_vec = nullptr;

    void init(unsigned rows, unsigned cols) {
        static_assert(std::is_copy_constructible<T>::value, "Type is not copy constructible");
        static_assert(std::is_move_assignable<T>::value, "Type is not move assignable");

        m_rows = rows;
        m_cols = cols;

        m_capacity = rows * cols;

        if (m_vec != nullptr)
            delete[] m_vec;

        m_vec = new T[m_capacity]();
        for (size_t i = 0; i < m_capacity; i++)
            m_vec[i] = T();
    }

    void copy(const Matrix<T> &other) {
        init(other.m_rows, other.m_cols);

        for (size_t i = 0; i < m_capacity; i++)
            m_vec[i] = T(other.m_vec[i]);
    }

    void move(Matrix<T> &&other) {
        m_capacity = other.m_capacity;
        m_rows = other.m_rows;
        m_cols = other.m_cols;

        m_vec = other.m_vec;
        other.m_vec = nullptr;
    }

    void check() const {
        if (m_vec == nullptr)
            throw std::out_of_range("Matrix is empty");
    }
};

#endif
