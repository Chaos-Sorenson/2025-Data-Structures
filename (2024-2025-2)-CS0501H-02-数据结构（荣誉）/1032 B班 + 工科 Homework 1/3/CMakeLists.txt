cmake_minimum_required(VERSION 3.28)
project(3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-omit-frame-pointer")
add_executable(3
#                main.cpp
#                main2.cpp
                main3.cpp
)
