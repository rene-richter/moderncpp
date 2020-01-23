cmake_minimum_required (VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#enable_testing()

project (InheritanceDemo)

add_executable(myprogram main.cpp arithmetic_sequence.cpp geometric_sequence.cpp)
