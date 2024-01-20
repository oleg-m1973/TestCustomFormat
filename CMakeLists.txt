cmake_minimum_required(VERSION 3.15)
project(TestCustomFormat)

include(common.cmake)

file(GLOB INC_LOCAL *.h)
file(GLOB SRC_LOCAL *.cpp)
file(GLOB C_SRC_LOCAL *.c)
  
add_executable(TestCustomFormat ${SRC_LOCAL} ${C_SRC_LOCAL} ${INC_LOCAL})

find_package(fmt CONFIG REQUIRED)
target_link_libraries(TestCustomFormat PRIVATE fmt::fmt)  


