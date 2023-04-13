cmake_minimum_required(VERSION 3.5)
project(LLVMPassLearn)
set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED)

add_subdirectory(lib)