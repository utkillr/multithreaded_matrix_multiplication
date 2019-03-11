#include <iostream>
#include <fstream>
#include <chrono>
#include <omp.h>
#include "matrix.h"
#include "exception/matrix_multiplication_exception.h"
#include "exception/matrix_initialization_exception.h"

int main() {
    std::ifstream inputFile1, inputFile2;
    Matrix *matrix1, *matrix2;
    std::ofstream outputFile;

    try {
        inputFile1.open("C:\\university\\multithreading\\matrix_multiplication\\flat_matrix1.txt");
        inputFile2.open("C:\\university\\multithreading\\matrix_multiplication\\flat_matrix2.txt");
        matrix1 = Matrix::fromInputStreamStress(inputFile1, 10 * 3);
        matrix2 = Matrix::fromInputStreamStress(inputFile2, 10 * 3);
    } catch (MatrixInitializationException e) {
        std::cout << e.what();
        return -1;
    }

    int dynamic = omp_get_dynamic();
    // Cores are suffocating at 4. So lets run up to 8 threads
    int maxThreads = 8;
    // We run 3 times to get avg
    int launchTimes = 3;

    omp_set_dynamic(0);

    outputFile.open("C:\\university\\multithreading\\matrix_multiplication\\output.csv");

    try {
        Matrix *multiplication;
        Matrix *multiplicationOMP;

        auto start = std::chrono::high_resolution_clock::now();
        multiplication = Matrix::multiply(matrix1, matrix2);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "No OMP time: " << duration.count() << std::endl;

        // Threads cycle
        for (int j = 1; j < launchTimes + 1; j++) {
            // Avg cycle
            for (int i = 1; i < maxThreads + 1; i++) {
                omp_set_num_threads(i);
                start = std::chrono::high_resolution_clock::now();
                multiplicationOMP = Matrix::multiplyOMP(matrix1, matrix2);
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                outputFile << duration.count() << ",";
                bool res = multiplication->equals(multiplicationOMP);
                std::cout << "Attempt: " << j << ". Threads: " << i << ". Right: "
                          << multiplication->equals(multiplicationOMP) << ". Time: " << duration.count() << std::endl;
                if (!res) {
                    delete multiplication;
                    delete multiplicationOMP;
                    throw MatrixMultiplicationException(matrix1, matrix2);
                }
                delete multiplicationOMP;
            }
            outputFile << std::endl;
        }
        delete multiplication;

    } catch (MatrixMultiplicationException e) {
        std::cout << e.what();
    }

    outputFile.close();

    omp_set_dynamic(dynamic);

    delete matrix1;
    delete matrix2;

    return 0;
}

/*
 * Open MP: Loop Parallelism
 * Умеет по разному параллелить For.
 *
 * Подумать: какими способами можно параллеить?
 * Попробовать разные способы параллелизма.
 *
 * Варианты: Параллелить форы (внешний, внутренний, средний)
 * Задача: придумать n решений, попробовать несколько.
 * Запускать по несколько раз, получать усредненное значение (по 3 раза at least)
 * Не использовать чистый parallel for - юзать reduce и прочее
 *
 * # ... scheduled (static, 1)
 * # ... scheduled (dynamic, 1)
 * # Погуглить про чанки
 * # Попробовать плохие матрицы (плоские, например)
 */