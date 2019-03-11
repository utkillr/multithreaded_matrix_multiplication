//
// Created by nosikk on 2/25/2019.
//

#include <cstring>
#include <omp.h>
#include "matrix.h"
#include "exception/matrix_initialization_exception.h"
#include "exception/matrix_multiplication_exception.h"

Matrix::Matrix(int height, int width) {
    this->width = width;
    this->height = height;
    this->a = new int*[height];
    for (int i = 0; i < height; i++) {
        this->a[i] = new int[width];
        std::fill(this->a[i], this->a[i] + width, 0);
    }
}

Matrix::Matrix(int** array, int height, int width) : Matrix(height, width) {
    try {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                this->a[i][j] = array[i][j];
            }
        }
    } catch (...) {
        throw MatrixInitializationException(false);
    }
}

Matrix::~Matrix() {
    delete this->a;
}

Matrix* Matrix::fromInputStream(std::ifstream &inputStream) {
    if (!inputStream) {
        std::cerr << "Unable to open provided file" << std::endl;
        std::cout << "Trying to open default inputFile: " << defaultInputFile << std::endl;
        inputStream.open(defaultInputFile);
    }
    if (!inputStream) {
        std::cerr << "Unable to open provided file at all" << std::endl;
        throw MatrixInitializationException(true);
    }

    int height, width;
    int **array;

    inputStream >> height;
    inputStream >> width;
    array = new int *[height];
    for (int i = 0; i < height; i++) {
        array[i] = new int[width];
        for (int j = 0; j < width; j++) {
            int a;
            inputStream >> a;
            array[i][j] = a;
        }
    }

    inputStream.close();

    return new Matrix(array, height, width);
}

Matrix* Matrix::fromInputStreamStress(std::ifstream &inputStream, int multiplier) {
    if (!inputStream) {
        std::cerr << "Unable to open provided file" << std::endl;
        std::cout << "Trying to open default inputFile: " << defaultInputFile << std::endl;
        inputStream.open(defaultInputFile);
    }
    if (!inputStream) {
        std::cerr << "Unable to open provided file at all" << std::endl;
        throw MatrixInitializationException(true);
    }

    int height, width;
    int **array;

    inputStream >> height;
    inputStream >> width;
    array = new int *[height * multiplier];
    for (int i = 0; i < height * multiplier; i++) {
        array[i] = new int[width * multiplier];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int a;
            inputStream >> a;
            for (int im = 0; im < multiplier; im++) {
                for (int jm = 0; jm < multiplier; jm++) {
                    array[im * height + i][jm * width + j] = a;
                }
            }
        }
    }

    inputStream.close();

    return new Matrix(array, height * multiplier, width * multiplier);
}

int Matrix::getWidth() {
    return this->width;
}

int Matrix::getHeight() {
    return this->height;
}

bool Matrix::equals(Matrix *matrix) {
    if (!this->height == matrix->getHeight() || !this->width == matrix->getWidth()) {
        return false;
    }
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->a[i][j] != matrix->a[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void Matrix::print(std::ostream &out) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            out << this->a[i][j] << " ";
        }
        out << std::endl;
    }
}

Matrix* Matrix::multiply(Matrix* matrix1, Matrix *matrix2) {
    // check if we can multiply
    if (matrix1->getWidth() != matrix2->getHeight()) {
        throw MatrixMultiplicationException(matrix1, matrix2);
    }
    else {
        auto *resultMatrix = new Matrix(matrix1->getHeight(), matrix2->getWidth());

        for (int i = 0; i < resultMatrix->getHeight(); i++) {
            for (int j = 0; j < resultMatrix->getWidth(); j++) {
                for (int r = 0; r < matrix1->getWidth(); r++) {
                    resultMatrix->a[i][j] += resultMatrix->a[i][j] + matrix1->a[i][r] * matrix2->a[r][j];
                }
            }
        }
        return resultMatrix;
    }
}

Matrix* Matrix::multiplyOMP(Matrix *matrix1, Matrix* matrix2) {
    // check if we can multiply
    if (matrix1->getWidth() != matrix2->getHeight()) {
        throw MatrixMultiplicationException(matrix1, matrix2);
    }
    else {
        auto *resultMatrix = new Matrix(matrix1->getHeight(), matrix2->getWidth());
        if (resultMatrix->getHeight() >= resultMatrix->getWidth()) {
            #pragma omp parallel for shared(matrix1, matrix2, resultMatrix) schedule(runtime)
            for (int i = 0; i < resultMatrix->getHeight(); i++) {
                for (int j = 0; j < resultMatrix->getWidth(); j++) {
                    for (int r = 0; r < matrix1->getWidth(); r++) {
                        resultMatrix->a[i][j] += resultMatrix->a[i][j] + matrix1->a[i][r] * matrix2->a[r][j];
                    }
                }
            }
        } else {
            #pragma omp parallel for shared(matrix1, matrix2, resultMatrix) schedule(runtime)
            for (int j = 0; j < resultMatrix->getWidth(); j++) {
                for (int i = 0; i < resultMatrix->getHeight(); i++) {
                    for (int r = 0; r < matrix1->getWidth(); r++) {
                        resultMatrix->a[i][j] += resultMatrix->a[i][j] + matrix1->a[i][r] * matrix2->a[r][j];
                    }
                }
            }
        }
        return resultMatrix;
    }
}

