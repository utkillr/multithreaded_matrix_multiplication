//
// Created by nosikk on 2/26/2019.
//

#ifndef MATRIX_MULTIPLICATION_MATRIX_MULTIPLICATION_EXCEPTION_H
#define MATRIX_MULTIPLICATION_MATRIX_MULTIPLICATION_EXCEPTION_H

#include <exception>
#include "../matrix.h"

class MatrixMultiplicationException : public std::exception {
private:
    int *sizes_1;
    int *sizes_2;

public:
    MatrixMultiplicationException(Matrix* matrix1, Matrix* matrix2);
    virtual const char * what () const noexcept;
};


#endif //MATRIX_MULTIPLICATION_MATRIX_MULTIPLICATION_EXCEPTION_H
