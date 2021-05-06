#pragma once

/*
This is a ROW MAJOR orientation matrix.
For a (m x n)-dimensional matrix and 0 <= i < m, 0 <= j < n every element
m(i, j) is mapped to the  (i x n + j)-th element of the container.

*/

#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace math {

class MatrixMN {
 public:
  // Constructor
  MatrixMN();

  MatrixMN(const size_t rows, const size_t cols);

  MatrixMN(const MatrixMN& m);

  // Constructor to make it possible to initialize with a double array
  template <size_t SIZE1, size_t SIZE2>
  explicit MatrixMN(const double (&arr)[SIZE1][SIZE2]) : mrows(SIZE1), mcols(SIZE2) {
    mdata = (SIZE1 * SIZE2 == 0) ? NULL : new double[SIZE1 * SIZE2];

    for (size_t row = 0; row < SIZE1; ++row) {
      for (size_t col = 0; col < SIZE2; ++col) {
        mdata[getIndex(row, col)] = arr[row][col];
      }
    }
  }

  // Destructor
  virtual ~MatrixMN();

  // Getters
  bool isEmpty() const;

  size_t size1() const;

  size_t size2() const;

  // Operators
  double& operator()(const size_t row, const size_t col);

  const double& operator()(const size_t row, const size_t col) const;

  MatrixMN& operator=(const MatrixMN& m);

  bool operator==(const MatrixMN& m) const;

  // compare elements of MatrixMN and array
  template <size_t SIZE1, size_t SIZE2>
  bool operator==(const double (&arr)[SIZE1][SIZE2]) const {
    MatrixMN MatrixtoCompareWith(arr);
    return operator==(MatrixtoCompareWith);
  }

  bool operator!=(const MatrixMN& m) const;

  // compare elements of MatrixMN and array
  template <size_t SIZE1, size_t SIZE2>
  bool operator!=(const double (&arr)[SIZE1][SIZE2]) const {
    return !operator==(arr);
  }

  MatrixMN operator+(const double& scalar) const;

  MatrixMN operator+(const MatrixMN& m) const;

  MatrixMN operator-(const double& scalar) const;

  MatrixMN operator-(const MatrixMN& m) const;

  MatrixMN operator*(const double& scalar) const;

  MatrixMN operator*(const MatrixMN& m) const;

  MatrixMN operator/(const double& scalar) const;

  MatrixMN& operator-();  // Overload '-' Unary Operator

  void operator+=(const double& scalar);

  void operator+=(const MatrixMN& m);

  void operator-=(const double& scalar);

  void operator-=(const MatrixMN& m);

  void operator*=(const double& scalar);

  // matrix operations
  void clear();

  MatrixMN transpose() const;

  MatrixMN& assign(const MatrixMN& m);

  bool is_same_size(const MatrixMN& m) const;

  void check_size(const MatrixMN& m) const;

  // Test if the Matrix m is near
  bool epsilonEquals(const MatrixMN& m, const double epsilon) const;

  friend std::ostream& operator<<(std::ostream&, const MatrixMN&);

 private:
  inline size_t getIndex(const size_t row, const size_t col) const { return mcols * row + col; }
  size_t mrows, mcols;
  double* mdata;
};

}  // namespace math