
#include "Matrix.h"


template<typename T>
Matrix<T>::Matrix(int Rows, int Columns) {
    numColumns = Columns;
    numRows = Rows;
    data = new T[numRows * numColumns];
}

template<typename T>
Matrix<T>::Matrix(int numRows, int numColumns, T *values) : Matrix(numRows, numColumns) {
    for (int i = 0; i < numRows * numColumns; i++)
        data[i] = values[i];
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other) : Matrix(other.numRows, other.numColumns) {
    for (int i = 0; i < numColumns * numRows; i++)
        data[i] = other.data[i];
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[]data;
}

template<typename T>
int Matrix<T>::getNumRows() const {
    return numRows;
}

template<typename T>
int Matrix<T>::getNumColumns() const {
    return numColumns;
}

template<typename T>
void Matrix<T>::setAllValues(const T &value) {
    for (int i = 0; i < numRows * numColumns; i++)
        data[i] = value;
}

template<typename T>
void Matrix<T>::setValue(int rowIndex, int columnIndex, const T &value) throw(out_of_range) {
    if (rowIndex < 0 || rowIndex >= numRows || columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");
    data[columnIndex + rowIndex * numColumns] = value;
}

template<typename T>
T Matrix<T>::getValue(int rowIndex, int columnIndex) const throw(out_of_range) {
    if (rowIndex < 0 || rowIndex >= numRows || columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");
    return data[columnIndex + rowIndex * numColumns];
}


template<typename T>
void Matrix<T>::setRow(int rowIndex, Matrix<T> rowMat) throw(out_of_range, invalid_argument) {
    if (rowIndex < 0 || rowIndex >= numRows)
        throw out_of_range("Indice non valido");

    if (numColumns != rowMat.numColumns || rowMat.numRows != 1)
        throw invalid_argument("Matrice di dimensioni non valide");

    for (int i = 0; i < numColumns; i++)
        this->data[i + this->numColumns * rowIndex] = rowMat.data[i];
}

template<typename T>
void Matrix<T>::setColumn(int columnIndex, Matrix<T> colMat) throw(out_of_range, invalid_argument) {
    if (columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indice non valido");

    if (numRows != colMat.numRows || colMat.numColumns != 1)
        throw invalid_argument("Matrice di dimensioni non valide");

    for (int i = 0; i < numRows; i++)
        this->data[i * this->numColumns + columnIndex] = colMat.data[i];
}

template<typename T>
Matrix<T> Matrix<T>::getRow(int rowIndex) const throw(out_of_range) {
    if (rowIndex < 0 || rowIndex >= numRows)
        throw out_of_range("Indice non valido");

    Matrix<T> output(1, numColumns);
    for (int i = 0; i < numColumns; i++)
        output.data[i] = this->data[this->numColumns * rowIndex + i];

    return output;
}

template<typename T>
Matrix<T> Matrix<T>::getColumn(int columnIndex) const throw(out_of_range) {
    if (columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indice non valido");

    Matrix<T> output(numRows, 1);
    for (int i = 0; i < numRows; i++)
        output.data[i] = this->data[i * this->numColumns + columnIndex];

    return output;
}


template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &other) const {
    if (numRows != other.numRows || numColumns != other.numColumns)
        return false;
    for (int i = 0; i < numRows * numColumns; i++)
        if (data[i] != other.data[i])
            return false;
    return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T> &other) const {
    return !(*this == other);
}

template<typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &other) {
    if (this != &other) {
        this->~Matrix();
        numRows = other.numRows;
        numColumns = other.numColumns;
        data = new T[numRows * numColumns];
        for (int i = 0; i < numRows * numColumns; i++)
            data[i] = other.data[i];
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const throw(invalid_argument) {
    if (numRows != other.numRows || numColumns != other.numColumns)
        throw invalid_argument("Dimensioni matrici differenti");

    Matrix<T> result(numRows, numColumns);
    for (int i = 0; i < numRows * numColumns; i++)
        result.data[i] = data[i] + other.data[i];
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const throw(invalid_argument) {
    if (numRows != other.numRows || numColumns != other.numColumns)
        throw invalid_argument("Dimensioni matrici differenti");

    Matrix<T> result(numRows, numColumns);
    for (int i = 0; i < numRows * numColumns; i++)
        result.data[i] = data[i] - other.data[i];
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const throw(invalid_argument) {
    if (numColumns != other.numRows)
        throw invalid_argument("Dimensioni non congrue per prodotto");

    Matrix<T> result(numRows, other.numColumns);
    result.setAllValues(0);
    for (int row = 0; row < numRows; row++)
        for (int col = 0; col < other.numColumns; col++)
            for (int i = 0; i < numColumns; i++)
                result.data[col + row * other.numColumns] +=
                        data[i + row * numColumns] * other.data[col + i * other.numColumns];

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T &scalar) const {
    Matrix<T> result(numRows, numColumns);
    for (int i = 0; i < numColumns * numRows; i++)
        result.data[i] = data[i] * scalar;
    return result;
}

template<typename T>
T &Matrix<T>::operator()(int rowIndex, int columnIndex) throw(out_of_range)
{
    if (rowIndex < 0 || rowIndex >= numRows || columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");
    return data[columnIndex + rowIndex * numColumns];
}

template<typename T>
Matrix<T> Matrix<T>::subMatrix(int excludingRow, int excludingColumn) const throw(logic_error, out_of_range) {
    if (numRows <= 1 || numColumns <= 1)
        throw logic_error("Matrice troppo piccola per estrarre una sottomatrice");

    if (excludingRow < 0 || excludingRow >= numRows || excludingColumn < 0 || excludingColumn >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");

    Matrix<T> result(numRows - 1, numColumns - 1);

    for (int col = 0; col < numColumns; col++) {
        if (col == excludingColumn)
            continue; //salta un iterazione del loop
        for (int row = 0; row < numRows; row++) {
            if (row == excludingRow)
                continue;
            int index =
                    (col > excludingColumn ? col - 1 : col) + (row > excludingRow ? row - 1 : row) * result.numColumns;
            result.data[index] = data[col + row * numColumns];
        }
    }

    return result;
}

template<typename T>
T Matrix<T>::determinant() const throw(logic_error) {
    if (numRows != numColumns)
        throw logic_error("Impossibile calcolare il determinante su una matrice non quadrata");

    if (numRows == 2)
        return data[0] * data[3] - data[1] * data[2];

    T det = 0;

    for (int col = 0; col < numColumns; col++)
        det += data[col] * subMatrix(0, col).determinant() * (col % 2 == 0 ? 1 : -1);

    return det;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(numColumns, numRows);

    for (int row = 0; row < numRows; row++)
        for (int col = 0; col < numColumns; col++)
            result.data[row + col * numRows] = data[col + row * numColumns];

    return result;
}

template<typename T>
string Matrix<T>::toString() const {
    string toReturn = "Matrix of " + to_string(numRows) + " rows and " + to_string(numColumns) + " columns:\n";
    for (int row = 0; row < numRows; row++) {
        toReturn += "\t";
        for (int col = 0; col < numColumns; col++)
            toReturn += " " + to_string(data[col + row * numColumns]);
        toReturn += "\n";
    }
    return toReturn;
}
