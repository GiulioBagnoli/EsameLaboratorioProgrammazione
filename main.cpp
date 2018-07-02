
#include <iostream>
#include "Matrix.cpp"


using namespace std;

int main() {
    Matrix<float> mat(4, 4);
    mat.setAllValues(7);
    mat.setValue(1,2,2);
    mat.setValue(3,3,6);
    mat.setValue(2,0,11);


    Matrix<float> trasposta = mat.transpose();
    Matrix<float> subMat = mat.subMatrix(0, 0);
    float determinante = mat.determinant();

    cout << "mat: " << mat.toString() << endl;
    cout << "determinante: " << determinante << endl;
    cout << "trasposta: " << trasposta.toString() << endl;
    cout << "subMat: " << subMat.toString() << endl;

}