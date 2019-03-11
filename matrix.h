//
// Created by nosikk on 2/25/2019.
//

#ifndef MATRIX_MULTIPLICATION_MATRIX_H
#define MATRIX_MULTIPLICATION_MATRIX_H

#include <algorithm>
#include <fstream>
#include <iostream>

class Matrix {
private:
    int width;
    int height;

    inline static const std::string defaultInputFile = "input.txt";
public:
    int** a;

    Matrix(int height, int width);
    Matrix(int** array, int height, int width);
    ~Matrix();

    static Matrix* fromInputStream(std::ifstream &inputStream);
    static Matrix* fromInputStreamStress(std::ifstream &inputStream, int multiplier);

    int getWidth();
    int getHeight();
    bool equals(Matrix *matrix);

    void print(std::ostream &out);

    static Matrix* multiply(Matrix *matrix1, Matrix *matrix2);
    static Matrix* multiplyOMP(Matrix *matrix1, Matrix *matrix2);
};

#endif //MATRIX_MULTIPLICATION_MATRIX_H
