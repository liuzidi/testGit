cmake_minimum_required(VERSION 3.25)
project(CPPProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPPProject main.cpp Person.cpp Person.h Cat.cpp Cat.h)
