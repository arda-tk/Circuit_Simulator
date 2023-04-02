cmake_minimum_required(VERSION 3.24)

project (cirSim C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c src/component.c src/visual.c src/calculator.c src/topology.c src/topology.c)

add_executable(cirSim ${SOURCE_FILES})

find_package(GSL REQUIRED)
target_link_libraries(cirSim GSL::gsl GSL::gslcblas)

