cmake_minimum_required(VERSION 3.12)
project(test_gsl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17")

add_executable(test_gsl src/main.cpp)
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIR})
target_link_libraries(test_gsl gsl )
