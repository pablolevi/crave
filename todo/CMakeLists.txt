if(APPLE)
  set(CMAKE_C_COMPILER clang)
  set(CMAKE_CXX_COMPILER clang++)
else()
  set(CMAKE_C_COMPILER /usr/bin/gcc-4.9)
  set(CMAKE_CXX_COMPILER /usr/bin/g++-4.9)
endif()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("The compiler is now ${CMAKE_CXX_COMPILER}.")

project(crave)
cmake_minimum_required(VERSION 2.8.9)
