#include "MatrixMN.h"
#include <cmath>

namespace math {
// Constructors
MatrixMN::MatrixMN() : mrows(0), mcols(0), mdata(NULL) {}

MatrixMN::MatrixMN(const size_t rows, const size_t cols) : mrows(rows), mcols(cols) {
  if (rows == 0 || cols == 0) {
    throw std::out_of_range("Matrix constructor has 0 size");
  }
  mdata = new double[rows * cols];
  std::fill(mdata, mdata + mrows * mcols, 0.0);
}

MatrixMN::MatrixMN(const MatrixMN& m) : mrows(m.mrows), mcols(m.mcols) {
  mdata = new double[m.mrows * m.mcols];
  std::copy(m.mdata, m.mdata + m.mrows * m.mcols, mdata);
}

MatrixMN::~MatrixMN() {
  if (mdata != NULL) {
    delete[] mdata;
  }
}

// Getters
bool MatrixMN::isEmpty() const {
  if (mdata == NULL) {
    return true;
  }
  return false;
}

size_t MatrixMN::size1() const {
  return mrows;
}

size_t MatrixMN::size2() const {
  return mcols;
}

// Operators
double& MatrixMN::operator()(const size_t row, const size_t col) {
  if (row >= mrows || col >= mcols) {
    throw std::out_of_range("Matrix subscript out of bounds");
  }
  return mdata[getIndex(row, col)];
}

const double& MatrixMN::operator()(const size_t row, const size_t col) const {
  if (row >= mrows || col >= mcols) {
    throw std::out_of_range("const Matrix subscript out of bounds");
  }
  return mdata[getIndex(row, col)];
}

MatrixMN& MatrixMN::operator=(const MatrixMN& m) {
  if (this == &m) {
    return *this;
  }
  // unallocate memory
  delete[] mdata;
  // assign
  mrows = m.mrows;
  mcols = m.mcols;
  mdata = new double[mrows * mcols];
  std::copy(m.mdata, m.mdata + mrows * mcols, mdata);

  return *this;
}

bool MatrixMN::operator==(const MatrixMN& m) const {
  if (this == &m) {
    return true;
  }
  if (m.mrows != mrows || m.mcols != mcols) {
    return false;
  }
  return std::equal(mdata, mdata + mrows * mcols, m.mdata);
}

bool MatrixMN::operator!=(const MatrixMN& m) const {
  return !(*this == m);
}

MatrixMN MatrixMN::operator+(const double& scalar) const {
  MatrixMN ret(mrows, mcols);
  std::transform(mdata, mdata + mrows * mcols, ret.mdata, std::bind2nd(std::plus<double>(), scalar));
  return ret;
}

MatrixMN MatrixMN::operator+(const MatrixMN& m) const {
  check_size(m);
  MatrixMN ret(mrows, mcols);
  std::transform(mdata, mdata + mrows * mcols, m.mdata, ret.mdata, std::plus<double>());
  return ret;
}

MatrixMN& MatrixMN::operator-() {
  std::transform(mdata, mdata + mrows * mcols, mdata, std::bind2nd(std::multiplies<double>(), -1));
  return *this;
}

MatrixMN MatrixMN::operator-(const double& scalar) const {
  MatrixMN difference(mrows, mcols);
  std::transform(mdata, mdata + mrows * mcols, difference.mdata, std::bind2nd(std::minus<double>(), scalar));
  return difference;
}

MatrixMN MatrixMN::operator-(const MatrixMN& m) const {
  check_size(m);
  MatrixMN difference(mrows, mcols);
  std::transform(mdata, mdata + mrows * mcols, m.mdata, difference.mdata, std::minus<double>());
  return difference;
}

MatrixMN MatrixMN::operator*(const double& scalar) const {
  MatrixMN product(mrows, mcols);
  std::transform(mdata, mdata + mrows * mcols, product.mdata, std::bind2nd(std::multiplies<double>(), scalar));
  return product;
}

MatrixMN MatrixMN::operator*(const MatrixMN& m) const {
  if (mcols != m.mrows) {
    std::ostringstream buffer;
    buffer << " Number of columns " << mcols << " must match to number of rows " << m.mrows << " .\n";
    throw std::logic_error(buffer.str());
  }
  MatrixMN product(mrows, m.mcols);
  for (size_t i = 0; i < mrows; ++i) {
    for (size_t j = 0; j < m.mcols; ++j) {
      double product_sum = 0.0;
      for (size_t k = 0; k < mcols; ++k) {
        product_sum += mdata[getIndex(i, k)] * m.mdata[m.getIndex(k, j)];
      }
      product.mdata[product.getIndex(i, j)] = product_sum;
    }
  }
  return product;
}

MatrixMN MatrixMN::operator/(const double& scalar) const {
  if (scalar == 0) {
    throw std::logic_error("Can not divide by zero.");
  }
  MatrixMN divide(mrows, mcols);
  std::transform(mdata, mdata + mrows * mcols, divide.mdata, std::bind2nd(std::divides<double>(), scalar));
  return divide;
}

void MatrixMN::operator+=(const double& scalar) {
  std::transform(mdata, mdata + mrows * mcols, mdata, std::bind2nd(std::plus<double>(), scalar));
}

void MatrixMN::operator+=(const MatrixMN& m) {
  check_size(m);
  std::transform(mdata, mdata + mrows * mcols, m.mdata, mdata, std::plus<double>());
}

void MatrixMN::operator-=(const double& scalar) {
  std::transform(mdata, mdata + mrows * mcols, mdata, std::bind2nd(std::minus<double>(), scalar));
}

void MatrixMN::operator-=(const MatrixMN& m) {
  check_size(m);
  std::transform(mdata, mdata + mrows * mcols, m.mdata, mdata, std::minus<double>());
}

void MatrixMN::operator*=(const double& scalar) {
  std::transform(mdata, mdata + mrows * mcols, mdata, std::bind2nd(std::multiplies<double>(), scalar));
}
// set all elements to zero.
void MatrixMN::clear() {
  std::fill(mdata, mdata + mrows * mcols, 0.0);
}

MatrixMN MatrixMN::transpose() const {
  MatrixMN trans(mcols, mrows);
  for (size_t i = 0; i < mrows; ++i) {
    for (size_t j = 0; j < mcols; ++j) {
      trans(j, i) = (*this)(i, j);
    }
  }
  return trans;
}

MatrixMN& MatrixMN::assign(const MatrixMN& m) {
  // unallocate
  delete[] mdata;
  // assign
  mrows = m.mrows;
  mcols = m.mcols;
  mdata = new double[mrows * mcols];
  std::copy(m.mdata, m.mdata + m.mrows * m.mcols, mdata);
  return *this;
}

inline bool MatrixMN::is_same_size(const MatrixMN& m) const {
  if (mrows == m.mrows && mcols == m.mcols) {
    return true;
  }
  return false;
}

inline void MatrixMN::check_size(const MatrixMN& m) const {
  if (this->is_same_size(m)) {
    return;
  } else {
    std::ostringstream buffer;
    buffer << " Number of rows and columns must match to [" << mrows << " , " << mcols << "].\n";
    throw std::logic_error(buffer.str());
  }
}

bool MatrixMN::epsilonEquals(const MatrixMN& m, const double epsilon) const {
  if (mdata == NULL || m.mdata == NULL || !is_same_size(m)) {
    return false;
  }

  for (size_t i = 0; i < mrows * mcols; ++i) {
    double absDiff = std::fabs(mdata[i] - m.mdata[i]);
    if (absDiff >= epsilon) {
      return false;
    }
  }
  return true;
}

// FRIEND
std::ostream& operator<<(std::ostream& os, const MatrixMN& matrix) {
  os << "[" << matrix.mrows << "," << matrix.mcols << "]\n";
  for (size_t i = 0; i < matrix.mrows; ++i) {
    for (size_t j = 0; j < matrix.mcols; ++j) {
      os << "|";
      os << std::setprecision(4) << std::setw(10) << matrix(i, j);
    }
    os << "|\n";
  }
  return os;
}

}  // namespace math