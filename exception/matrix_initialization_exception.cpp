//
// Created by nosikk on 2/26/2019.
//

#include "matrix_initialization_exception.h"

MatrixInitializationException::MatrixInitializationException(bool ifstreamConstructor) {
    this->ifstreamConstructor = ifstreamConstructor;
}

const char* MatrixInitializationException::what() const noexcept {
    if (this->ifstreamConstructor) {
        return "Error initializing matrix using provided ifstream";
    } else {
        return "Error initializing matrix";
    }
}
