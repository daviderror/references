cmake_minimum_required(VERSION 3.0)

project(xdma_rd_wr_test)

add_executable(xdma_rd_wr_test src/main.cpp)

install(TARGETS xdma_rd_wr_test RUNTIME DESTINATION bin)
