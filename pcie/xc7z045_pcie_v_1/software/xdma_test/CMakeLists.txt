cmake_minimum_required(VERSION 3.0)

project(xdma_test)

include_directories(inc/)

add_executable(xdma_test src/main.cpp src/xdma_test)

install(TARGETS xdma_test RUNTIME DESTINATION bin)
