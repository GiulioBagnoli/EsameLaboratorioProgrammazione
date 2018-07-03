

#ifndef MATRICI_MATRIX_H
#define MATRICI_MATRIX_H

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
public:
    Matrix(int numRows, int numColumns);

    Matrix(int numRows, int numColumns, T *values);

    Matrix(const Matrix<T> &other);

    ~Matrix();

    int getNumColumns() const;

    int getNumRows() const;

    void setAllValues(const T &value);

    void setValue(int rowIndex, int columnIndex, const T &value) throw(out_of_range);

    T getValue(int rowIndex, int columnIndex) const throw(out_of_range);

    void setRow(int rowIndex, Matrix<T> rowMat) throw(out_of_range, invalid_argument);

    void setColumn(int columnIndex, Matrix<T> colMat) throw(out_of_range, invalid_argument);

    Matrix<T> getRow(int rowIndex) const throw(out_of_range);

    Matrix<T> getColumn(int columnIndex) const throw(out_of_range);

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &other) const;

    Matrix <T> operator=(const Matrix<T> &other);

    Matrix<T> operator+(const Matrix<T> &other) const throw(invalid_argument);

    Matrix<T> operator-(const Matrix<T> &other) const throw(invalid_argument);

    Matrix<T> operator*(const Matrix<T> &other) const throw(invalid_argument);

    Matrix<T> operator*(const T &scalar) const;

    T &operator()(int rowIndex, int columnIndex) throw(out_of_range);

    Matrix<T> subMatrix(int excludingRow, int excludingColumn) const throw(logic_error, out_of_range);

    T determinant() const throw(logic_error);

    Matrix<T> transpose() const;

    string toString() const;

private:
    int numRows, numColumns;
    T *data;
};


#endif //MATRICI_MATRIX_H
