//
// Created by nosikk on 3/11/2019.
//

#ifndef MATRIX_MULTIPLICATION_MATRIX_MULTIPLICATION_RESULT_EXCEPTION_H
#define MATRIX_MULTIPLICATION_MATRIX_MULTIPLICATION_RESULT_EXCEPTION_H


class MatrixMultiplicationResultException : public std::exception {
public:
    MatrixMultiplicationResultException();
    virtual const char * what () const noexcept;
};

#endif //MATRIX_MULTIPLICATION_MATRIX_MULTIPLICATION_RESULT_EXCEPTION_H
