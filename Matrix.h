

#ifndef MATRICI_MATRIX_H
#define MATRICI_MATRIX_H

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename t>
class Matrix {
public:
    Matrix(int numRows, int numColumns);

    Matrix(int numRows, int numColumns, t *values);

    Matrix(const Matrix<t> &other);

    ~Matrix();

    int getNumColumns() const;

    int getNumRows() const;

    void setAllValues(const t &value);

    void setValue(int rowIndex, int columnIndex, const t &value) throw(out_of_range);

    t getValue(int rowIndex, int columnIndex) const throw(out_of_range);

    void setRow(int rowIndex, Matrix<t> rowMat) throw(out_of_range, invalid_argument);

    void setColumn(int columnIndex, Matrix<t> colMat) throw(out_of_range, invalid_argument);

    Matrix<t> getRow(int rowIndex) const throw(out_of_range);

    Matrix<t> getColumn(int columnIndex) const throw(out_of_range);

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &other) const;

    Matrix<t> operator=(const Matrix<t> &other);

    Matrix<t> operator+(const Matrix<t> &other) const throw(invalid_argument);

    Matrix<t> operator-(const Matrix<t> &other) const throw(invalid_argument);

    Matrix<t> operator*(const Matrix<t> &other) const throw(invalid_argument);

    Matrix<t> operator*(const t &scalar) const;

    t &operator()(int rowIndex, int columnIndex) throw(out_of_range);

    Matrix<t> subMatrix(int excludingRow, int excludingColumn) const throw(logic_error, out_of_range);

    t determinant() const throw(logic_error);

    Matrix<t> transpose() const;

    string toString() const;

private:
    int numRows, numColumns;
    t *data;
};


#endif //MATRICI_MATRIX_H
