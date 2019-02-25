//
// Created by nosikk on 2/26/2019.
//

#ifndef MATRIX_MULTIPLICATION_MATRIX_INITIALIZATION_EXCEPTION_H
#define MATRIX_MULTIPLICATION_MATRIX_INITIALIZATION_EXCEPTION_H

#include <exception>

class MatrixInitializationException : public std::exception {
private:
    bool ifstreamConstructor;
public:
    MatrixInitializationException(bool ifstreamConstructor);
    virtual const char * what () const noexcept;
};


#endif //MATRIX_MULTIPLICATION_MATRIX_INITIALIZATION_EXCEPTION_H
