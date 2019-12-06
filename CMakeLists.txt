cmake_minimum_required(VERSION 3.10.2)
project(oop_exercise_06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g3")
add_executable(oop_exercise_06 main.cpp mylist.h mystack.h point.h pentagon.h myallocator.h)
