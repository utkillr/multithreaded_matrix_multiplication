//
// Created by nosikk on 2/26/2019.
//

#include "matrix_multiplication_exception.h"

#include <sstream>

MatrixMultiplicationException::MatrixMultiplicationException(Matrix *matrix1, Matrix *matrix2) {
    this->sizes_1 = new int[2] {matrix1->getHeight(), matrix1->getWidth()};
    this->sizes_2 = new int[2] {matrix2->getHeight(), matrix2->getWidth()};
}

const char* MatrixMultiplicationException::what() const noexcept {
    std::ostringstream stringStream;
    stringStream << "Error multiplication matrices: sizes do not correspond: ("
        << this->sizes_1[0] << ", " << this->sizes_1[1] << ") and ("
        << this->sizes_2[0] << ", " << this->sizes_2[1] << "). Shall be (l, m) and (m, n)";
    return stringStream.str().c_str();
}