cmake_minimum_required(VERSION 3.28)
project(list)

set(CMAKE_CXX_STANDARD 20)

add_executable(list
        class-bint.hpp
        class-integer.hpp
        class-matrix.hpp
        algorithm.hpp
        exceptions.hpp
        list.hpp
        utility.hpp
#        code1.cpp
#        code2.cpp
#        code3.cpp
#        code4.cpp
#        code5.cpp
#        code6.cpp
#        real-data1.cpp
#        real-data2.cpp
        real-data3.cpp
)
