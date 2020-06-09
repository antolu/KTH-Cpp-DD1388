cmake_minimum_required(VERSION 3.10)

project(Cpp-DD1388)
set (CMAKE_CXX_STANDARD 17)

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

add_executable(chess
               06-chess/chessboard.cpp
               06-chess/chesspiece.cpp
               06-chess/ai.cpp
               06-chess/chesspieces.cpp
               06-chess/gameengine.cpp
               06-chess/main.cpp
               06-chess/tests_boards.cpp 06-chess/tests_ai.cpp)

target_link_libraries(count_if_followed_by gtest)
target_link_libraries(chess gtest)