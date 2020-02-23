cmake_minimum_required(VERSION 3.10)

project(Knapsack)

if(NOT MSVC)
    add_definitions("-std=c++17 -Wall -g")
else()
    add_definitions("-std=c++17 -WX -W2")
endif()

enable_testing()

file(GLOB SOURCES
  *.hpp
  *.cpp
)

include(GoogleTest)

add_executable(knapsack 
    main.cpp
    ${SOURCES}
)

add_test(Knapsack knapsack)

target_link_libraries(knapsack gtest)