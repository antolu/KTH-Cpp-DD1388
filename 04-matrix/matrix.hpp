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

template <class T>
class Matrix{
  
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

  friend Matrix<T> operator*(const Matrix<T> &lhs, const T &rhs) {
    Matrix<T> ret(lhs.m_rows, lhs.m_cols);
    
    for (size_t i = 0; i < lhs.m_capacity; i++)
      ret.m_vec[i] = lhs.m_vec[i] * rhs;
    
    return ret;
  }

  friend Matrix<T> operator*(const T &lhs, const Matrix<T> &rhs) {
    return rhs * lhs;
  }

  friend bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    lhs.check(); rhs.check();
    
    if (&lhs == &rhs)
      return true;
    
    if (lhs.m_rows != rhs.m_rows || lhs.m_cols != rhs.m_cols)
      return false;

    if (lhs.m_capacity != rhs.m_capacity)
      return false;

    for (size_t i = 0; i < lhs.m_capacity; i++)
      if (lhs.m_vec[i] != rhs.m_vec[i])
	return false;

    return true;
  }

  friend bool operator !=(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    return !(lhs == rhs);
  }

  const Matrix<T>& operator+=(const Matrix<T> &other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols)
      throw std::out_of_range("Dimensions do not match!");

    for (size_t i = 0; i < m_capacity; i++)
      m_vec[i] += other.m_vec[i];

    return *this;
  }

  const Matrix<T>& operator+=(const T &scalar) {
    for (size_t i = 0; i < m_capacity; i++)
      m_vec[i] += scalar;

    return *this;
  }
    
  const Matrix<T>& operator-=(const Matrix<T> &other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols)
      throw std::out_of_range("Dimensions do not match!");

    for (size_t i = 0; i < m_capacity; i++)
      m_vec[i] -= other.m_vec[i];

    return *this;
  }

  const Matrix<T>& operator-=(const T &scalar) {

    for (size_t i = 0; i < m_capacity; i++)
      m_vec[i] -= scalar;

    return *this;
  }
  
  const Matrix<T>& operator*=(const Matrix<T> &other) {
    if (m_cols != other.m_rows)
      throw std::out_of_range("Dimensions do not match!");

    size_t m = m_rows;
    size_t n = other.m_cols;
    T * ret = new T [m * n]();

    /* a(i, j) = a.m_vec[i * n + j] */
    for (size_t i = 0; i < m_rows; i++)
      for (size_t j = 0; j < other.m_cols; j++)
	for (size_t k = 0; k < other.m_rows; k++)
	  ret[i * n + j] += m_vec[i * m_cols + k] * other.m_vec[k * other.m_cols + j];

    delete[] m_vec;
    m_vec = ret;
    m_cols = n;
    m_capacity = m * n;

    return *this;
  }

  const Matrix<T>& operator*=(const T & scalar) {
    for (size_t i = 0; i < m_capacity; i++)
      m_vec[i] *= scalar;
	
    return *this;
  }

  friend std::ostream& operator<<(std::ostream & ostream, const Matrix<T> &mtx) {
    ostream << std::setprecision(3) << "[";
    for (size_t i = 0; i < mtx.m_rows; i++) {
      ostream << "[ ";
      for (size_t j = 0; j < mtx.m_cols; j++) {
	ostream << mtx.m_vec[i * mtx.m_cols + j] << " ";
      }
      ostream << "]";
      if (i != mtx.m_rows - 1)
	ostream << "\n";
    }
    ostream << "]";

    return ostream;
  }
  
  friend std::istream& operator>>(std::istream & istream, Matrix<T> &mtx) {

    char c;
    c = istream.get();
    if (c != '[' || c == EOF)
      throw std::out_of_range("Incorrect matrix format");
    
    for (size_t i = 0; i < mtx.m_rows; i++) {
      c = istream.get();
      if (c != '[' || c == EOF)
	throw std::out_of_range("Incorrect matrix format");
      
      for (size_t j = 0; j < mtx.m_cols; j++) {
	if (istream.peek() == EOF)
	  throw std::out_of_range("Too few elements to fit in a matrix");
	istream >> mtx.m_vec[i * mtx.m_cols + j];
      }
      c = istream.get();

      if (c != ']' || c == EOF)
	throw std::out_of_range("Incorrect matrix format");

      /* Skip newlines */
      if (istream.peek() == '\n')
	istream.get();
    }
    
    c = istream.get();
    if (c != ']' || c == EOF)
      throw std::out_of_range("Incorrect matrix format");
      
    return istream;
  }

  /* Kattis format */
  // friend std::istream& operator>>(std::istream & istream, Matrix<T> &mtx) {

  //   istream >> mtx.m_rows >> mtx.m_cols;
  //   mtx.init(mtx.m_rows, mtx.m_cols);

  //   for (size_t i = 0; i < mtx.m_capacity; i++)
  //     istream >> mtx.m_vec[i];
    
  //   return istream;
  // }

  Matrix<T> pointwiseMult(const Matrix<T> &other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols)
      throw std::out_of_range("Matrix dimensions don't match");

    Matrix<T> ret(m_rows, m_cols);

    for (size_t i = 0; i < m_capacity; i++)
      ret.m_vec[i] = m_vec[i] * other.m_vec[i];

    return ret;
  }

   // methods
  int rows() const {
    return m_rows;
  }
  
  int columns() const {
    return m_cols;
  }
  
  void reset() {
    for (size_t i = 0; i < m_capacity; i++)
      m_vec[i] = T();
  }
    

  static Matrix<T> eye(unsigned size) {
    Matrix<T> ret(size, size);

    for (size_t i = 0; i < size; i++)
      for (size_t j = 0; j < size; j++) {
	if (i == j)
	    ret.m_vec[i * size + j] = 1;
	else
	  ret.m_vec[i * size + j] = T();
      }
    

    return ret;
  }

  void insert_row(unsigned row) {
    if (row >= m_rows)
      throw std::out_of_range("Row number out of range");
    
    T * resized = new T [m_capacity + m_cols];

    unsigned k = 0;
    for (size_t i = 0; i < m_rows + 1; i++) {
      if (i >= row)
	k = i - 1;
      else
	k = i;

      for (size_t j = 0; j < m_cols; j++) {
	if (i == row) 
	  resized[i * m_cols + j] = T();
	else
	  resized[i * m_cols + j] = std::move(m_vec[k * m_cols + j]);
      }
    }

    m_rows++;
    m_capacity += m_cols;
    delete[] m_vec;
    m_vec = resized;
  }
  
  void append_row(unsigned row) {
    if (row >= m_rows)
      throw std::out_of_range("Row number out of range");
    
    T * resized = new T [m_capacity + m_cols];

    unsigned k = 0;
    for (size_t i = 0; i < m_rows + 1; i++) {
      if (i > row)
	k = i - 1;
      else
	k = i;

      for (size_t j = 0; j < m_cols; j++) {
	if (i == row + 1) 
	  resized[i * m_cols + j] = T();
	else
	  resized[i * m_cols + j] = std::move(m_vec[k * m_cols + j]);
      }
    }

    m_rows++;
    m_capacity += m_cols;
    delete[] m_vec;
    m_vec = resized;
  }
  
  void remove_row(unsigned row) {
    if (row >= m_rows)
      throw std::out_of_range("Row number out of range");
    
    unsigned k = 0;
    for (size_t i = 0; i < m_rows; i++) {
      if (i >= row)
	k = i + 1;
      else
	k = i;

      for (size_t j = 0; j < m_cols; j++) {
	if (i == m_rows - 1)
	  m_vec[i * m_cols + j] = 0;
	else
	  m_vec[i * m_cols + j] = m_vec[k * m_cols + j];
      }
    }

    m_rows--;
    m_capacity -= m_cols;
  }
  
  void insert_column(unsigned column) {
    if (column >= m_cols)
      throw std::out_of_range("Column number out of range");
    
    T * resized = new T [m_capacity + m_rows];

    unsigned k = 0;
    for (size_t i = 0; i < m_cols + 1; i++) {
      if (i >= column)
	k = i - 1;
      else
	k = i;

      for (size_t j = 0; j < m_rows; j++) {
	if (i == column)
	  resized[j * (m_cols + 1) + i] = T();
	else
	  resized[j * (m_cols + 1) + i] = std::move(m_vec[j * m_cols + k]);
      }
    }

    m_cols++;
    m_capacity += m_rows;
    delete[] m_vec;
    m_vec = resized;
  }
  
  void append_column(unsigned column) {
    if (column >= m_cols)
      throw std::out_of_range("Column number out of range");
    
    T * resized = new T [m_capacity + m_rows];

    unsigned k = 0;
    for (size_t i = 0; i < m_cols + 1; i++) {
      if (i > column)
	k = i - 1;
      else
	k = i;

      for (size_t j = 0; j < m_rows; j++) {
	if (i == column + 1)
	  resized[j * (m_cols + 1) + i] = T();
	else
	  resized[j * (m_cols + 1) + i] = std::move(m_vec[j * m_cols + k]);
      }
    }

    m_cols++;
    m_capacity += m_rows;
    delete[] m_vec;
    m_vec = resized;
  }
  
  void remove_column(unsigned column) {
    if (column >= m_cols)
      throw std::out_of_range("Column number out of range");

    for (size_t i = 0; i < m_rows; i++) {
      for (size_t j = 0; j < m_cols; j++) {
	if (j >= column)
	  m_vec[i * (m_cols - 1) + j] = std::move(m_vec[i * m_cols + (j - column + 1)]);
	else
	  m_vec[i * (m_cols - 1) + j] = std::move(m_vec[i * m_cols + j]);
      }
    }
    
    for (size_t j = m_capacity - m_rows; j < m_capacity; j++)
      m_vec[j] = 0;

    m_cols--;
    m_capacity -= m_rows;
  }

  Matrix<T> getColumn(unsigned column) const {
    if (column >= m_cols )
      throw std::out_of_range("Specified column is out of bounds");

    Matrix ret(m_rows, 1);

    for (size_t i = 0; i < m_rows; i++)
      ret.m_vec[i] = m_vec[i * m_cols + column];

    return ret;
  }

  Matrix<T> getRow(unsigned row) const {
    if (row >= m_rows )
      throw std::out_of_range("Specified row is out of bounds");

    Matrix ret(1, m_cols);

    for (size_t j = 0; j < m_cols; j++)
      ret.m_vec[j] = m_vec[row * m_cols + j];

    return ret;
  }

  const Matrix<T>& transpose() {
    if (m_rows == m_cols)
      for (size_t i = 0; i < m_rows; i++) {
	for (size_t j = 0; j < i; j++) {
	  T temp = std::move(m_vec[j * m_cols + i]);
	  m_vec[j * m_cols + i] = std::move(m_vec[i * m_cols + j]);
	  m_vec[i * m_cols + j] = std::move(temp);
	}
      }
    else {
      for (size_t i = 0; i < m_capacity; i++) {
	size_t idx = i;
	do { /* Calculate index in the original array */
	  idx = (idx % m_rows) * m_cols + (idx / m_rows);
	} while (idx < i);
	std::swap(m_vec[i], m_vec[idx]);
      }
    } 

    size_t t = m_cols;
    m_cols = m_rows;
    m_rows = t;

    return *this;
  }
  
  typedef T* iterator;
  
  iterator begin() const {
    return m_vec;
  }
  
  iterator end() const {
    return m_vec + m_capacity;
  }
  
private:
  size_t m_rows = 0;
  size_t m_cols = 0;
  size_t m_capacity = 0;
  T * m_vec = nullptr;

  void init(unsigned rows, unsigned cols)  {
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
