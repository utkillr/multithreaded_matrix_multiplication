//
// Created by nosikk on 3/11/2019.
//

#include <sstream>
#include "matrix_multiplication_result_exception.h"

MatrixMultiplicationResultException::MatrixMultiplicationResultException() {}

const char* MatrixMultiplicationResultException::what() const noexcept {
    std::ostringstream stringStream;
    stringStream << "Error multiplication matrices: Result is not correct";
    return stringStream.str().c_str();
}