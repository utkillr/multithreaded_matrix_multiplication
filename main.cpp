#include <iostream>
#include <fstream>
#include <chrono>
#include "matrix.h"
#include "exception/matrix_multiplication_exception.h"
#include "exception/matrix_initialization_exception.h"

#define STRESS

int main() {
    std::ifstream inputFile1, inputFile2;
    Matrix *matrix1, *matrix2;

    try {
        inputFile1.open("C:\\university\\multithreading\\matrix_multiplication\\matrix1.txt");
        inputFile2.open("C:\\university\\multithreading\\matrix_multiplication\\matrix2.txt");

        #ifdef STRESS
        matrix1 = Matrix::fromInputStreamStress(inputFile1, 30);
        matrix2 = Matrix::fromInputStreamStress(inputFile2, 30);

        #else
        matrix1 = Matrix::fromInputStream(inputFile1);
        matrix2 = Matrix::fromInputStream(inputFile2);

        #endif

    } catch (MatrixInitializationException e) {
        std::cout << e.what();
    }

    #ifdef STRESS
    std::cout << "Matrix 1: (" << matrix1->getHeight() << ", " << matrix1->getWidth() << ")" << std::endl;
    std::cout << "Matrix 2: (" << matrix2->getHeight() << ", " << matrix2->getWidth() << ")" << std::endl;

    #else
    std::cout << "Matrix 1:" << std::endl;
    matrix1->print(std::cout);
    std::cout << std::endl << "Matrix 2:" << std::endl;
    matrix2->print(std::cout);

    #endif

    try {
        Matrix *multiplication;

        auto start2 = std::chrono::high_resolution_clock::now();
        multiplication = Matrix::multiply(matrix1, matrix2);
        auto stop2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
        std::cout << std::endl << "Multiplication:     " << duration2.count() << std::endl;
        // multiplication->print(std::cout);
        delete multiplication;

        auto start1 = std::chrono::high_resolution_clock::now();
        multiplication = Matrix::multiplyOMP(matrix1, matrix2);
        auto stop1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
        std::cout << std::endl << "Multiplication OMP: " << duration1.count() << std::endl;
        // multiplication->print(std::cout);
        delete multiplication;
    } catch (MatrixMultiplicationException e) {
        std::cout << e.what();
    }

    delete matrix1;
    delete matrix2;

    return 0;
}