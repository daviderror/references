cmake_minimum_required(VERSION 3.0)

project(udp_client)

include_directories(inc/)

add_executable(udp_client 
               src/main.cpp
               src/udp_client.cpp 
               src/udp.cpp)

install(TARGETS udp_client RUNTIME DESTINATION bin)
