

#include "gtest/gtest.h"
#include "../Matrix.cpp"

TEST(Matrix, Constructor_Set_Get) {
    const int defValue = 11;
    Matrix<int> m(6, 9);
    m.setAllValues(defValue);
    ASSERT_EQ(m.getNumRows(), 6);
    ASSERT_EQ(m.getNumColumns(), 9);
    ASSERT_EQ(m.getValue(1, 1), defValue);
    ASSERT_THROW(m.getValue(7, 3), out_of_range);
    m.setValue(1,1, 0);
    ASSERT_EQ(m.getValue(1,1), 0);
    ASSERT_THROW(m.setValue(10,1,0), out_of_range);

    Matrix<int> m1(6, 1);
    m1.setAllValues(1);
    m.setColumn(3, m1);
    ASSERT_TRUE(m1 == m.getColumn(3));
    Matrix <int> m3 (5,1);
    ASSERT_THROW(m.getColumn(10), out_of_range);
    ASSERT_THROW(m.setColumn(1, m3), invalid_argument );
    ASSERT_THROW(m.setColumn(10, m1), out_of_range );


    Matrix<int> m2(1, 9);
    m2.setAllValues(3);
    m.setRow(4, m2);
    ASSERT_TRUE(m2 == m.getRow(4));
    Matrix <int> m4 (1,8);
    ASSERT_THROW(m.getRow(7), out_of_range);
    ASSERT_THROW(m.setRow(7, m2), out_of_range );
    ASSERT_THROW(m.setRow(1, m4), invalid_argument );
}

TEST(Matrix, Operators) {
    Matrix<int> m1(4, 3), m2(3, 2), m3(4, 3), m4(4, 3), m5(4, 2);
    m1.setAllValues(0);
    m2.setAllValues(1);
    m3.setAllValues(0);
    m4.setAllValues(0);
    m5.setAllValues(0);
    m1.setValue(3, 2, 4);
    m3.setValue(3, 2, 4);

    // operator ==
    ASSERT_EQ(m1, m3);

    // operator !=
    ASSERT_NE(m1, m2);
    m3.setValue(1, 1, 1);
    ASSERT_NE(m1, m3);

    // operator =
    m1 = m3;
    ASSERT_EQ(m1, m3);

    // operator -
    ASSERT_EQ(m1 - m3, m4);
    ASSERT_THROW(m1 - m2, invalid_argument);

    // operator +
    m4.setValue(3, 2, 8);
    m4.setValue(1, 1, 2);
    ASSERT_EQ(m1 + m3, m4);
    ASSERT_THROW(m1 + m2, invalid_argument);

    // operator * (scalar)
    m4.setValue(3, 2, 20);
    m4.setValue(1, 1, 5);
    ASSERT_EQ(m1 * 5, m4);

    // operator *
    ASSERT_THROW(m1 * m3, invalid_argument);
    m2.setValue(2, 1, 2);
    m5.setValue(1, 0, 1);
    m5.setValue(1, 1, 1);
    m5.setValue(3, 0, 4);
    m5.setValue(3, 1, 8);
    ASSERT_EQ(m1 * m2, m5);

    // operator ()
    ASSERT_EQ(m1.getValue(3, 1), m1(3, 1));
    ASSERT_THROW(m1(3, 3), out_of_range);
    m1(1, 2) = 96;
    ASSERT_EQ(m1(1, 2), 96);
}

TEST(Matrix, SubMatrix) {
    Matrix<int> mat(4, 3);
    mat.setAllValues(1);
    mat.setValue(0, 0, 0);
    mat.setValue(2, 0, 3);
    mat.setValue(1, 1, 4);
    mat.setValue(3, 2, 5);

    Matrix <int> subMat = mat.subMatrix(2, 1);
    Matrix <int> mat1 (1,1);
    ASSERT_EQ(subMat.getValue(0, 0), 0);
    ASSERT_EQ(subMat.getValue(1, 1), 1);
    ASSERT_EQ(subMat.getValue(2, 1), 5);
    ASSERT_THROW(mat.subMatrix(4,3), out_of_range);
    ASSERT_THROW(mat1.subMatrix(1,1), logic_error);
}

TEST(Matrix, Determinant) {
    Matrix<int> errMat(3, 2);
    ASSERT_THROW(errMat.determinant(), logic_error);

    Matrix<int> mat(3, 3);
    mat.setAllValues(1);
    mat.setValue(0, 0, 0);
    mat.setValue(1, 0, 2);
    mat.setValue(1, 1, 4);
    mat.setValue(2, 1, 2);
    ASSERT_EQ(mat.determinant(), -1);
}

TEST(Matrix, Transpose) {
    Matrix<float> mat(3, 2);
    mat.setAllValues(0);
    mat.setValue(1, 1, 1);
    mat.setValue(2, 1, 3);
    Matrix<float> trMat = mat.transpose();

    ASSERT_EQ(trMat.getNumRows(), 2);
    ASSERT_EQ(trMat.getNumColumns(), 3);
    ASSERT_EQ(trMat.getValue(0, 0), 0);
    ASSERT_EQ(trMat.getValue(1, 1), 1);
    ASSERT_EQ(trMat.getValue(1, 2), 3);
}