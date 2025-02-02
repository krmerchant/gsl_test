cmake_minimum_required(VERSION 3.12)
project(test_gsl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17")

#include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)

# hate to have to add this
add_subdirectory(googletest)

add_executable(test_gsl src/test_line_fit.cc )
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIR})
target_link_libraries(test_gsl gsl gmock_main gmock gtest_main gtest pthread )



add_executable(line_eval src/line_eval.cc )
target_link_libraries(line_eval gsl ${CSV_LIBRARIES} pthread)