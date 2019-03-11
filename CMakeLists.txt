cmake_minimum_required(VERSION 3.12)
project(matrix_multiplication)

# OpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

set(CMAKE_CXX_STANDARD 17)

add_executable(matrix_multiplication main.cpp matrix.h matrix.cpp exception/matrix_multiplication_exception.cpp exception/matrix_multiplication_exception.h exception/matrix_initialization_exception.cpp exception/matrix_initialization_exception.h exception/matrix_multiplication_result_exception.cpp exception/matrix_multiplication_result_exception.h)