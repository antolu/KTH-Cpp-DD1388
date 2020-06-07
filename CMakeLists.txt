cmake_minimum_required(VERSION 3.10)

project(Cpp-DD1388)

if(NOT MSVC)
    add_definitions("-std=c++17 -Wall -g")
else()
    add_definitions("-std=c++17 -WX -W2")
endif()

enable_testing()

include(GoogleTest)

add_executable(weird
    01-intro/weird.cpp
)

add_executable(count_if_followed_by
    01-intro/tests.cpp
    01-intro/count_if_followed_by.cpp
)

add_executable(01_complex
    01-intro/complex.cpp
)

add_executable(bad_plumbing
    01-intro/bad_plumbing.cpp
)

add_executable(complex
    02-complex/tests.cpp
    02-complex/Complex.cpp
)

add_executable(bintree-testbalance
    03-bintree/bintree.cpp
    03-bintree/testbalance.cpp
)

add_executable(bintree
    03-bintree/bintree.cpp
    03-bintree/testtree.cpp
)

add_executable(matrix
    04-matrix/tests.cpp
)

add_executable(pointers
    05-pointers/pointers.cpp
)

add_executable(lambdas
    05-pointers/lambda.cpp
)

add_executable(gnu
    05-pointers/gnu.cpp
    05-pointers/hyenasandgnus.cpp
    05-pointers/watermanager.cpp
)

add_executable(knapsack
    07-knapsack/knapsack.cpp
    07-knapsack/main.cpp
)

target_link_libraries(count_if_followed_by gtest)
target_link_libraries(complex gtest)
target_link_libraries(bintree gtest)
target_link_libraries(bintree-testbalance gtest)
target_link_libraries(matrix gtest)
target_link_libraries(gnu pthread)
target_link_libraries(knapsack gtest)

