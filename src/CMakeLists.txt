cmake_minimum_required(VERSION 3.13.5)

project(CodetronikPass)

find_package(LLVM PATHS "${LLVM_DIR}" REQUIRED CONFIG NO_DEFAULT_PATH)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
link_directories(${LLVM_LIBRARY_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")

add_library(CodetronikPass SHARED RegisterPass.cpp)

target_include_directories(CodetronikPass PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(CodetronikPass PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(CodetronikPass LLVMCore LLVMSupport LLVMTransformUtils)

add_subdirectory(AntiFunctionDecompile)
