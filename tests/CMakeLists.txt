cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_STANDARD 11)

set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu)
file(GLOB_RECURSE SOURCE ../src/*c)

include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})



add_executable(Matrix_test test_matrix.c ${SOURCE})
target_link_libraries(Matrix_test check)
target_link_libraries(Matrix_test subunit)
target_link_libraries(Matrix_test m)
add_test(NumericalMath Matrix_test)