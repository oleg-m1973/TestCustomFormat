cmake_minimum_required(VERSION 3.27)
project(TestCustomFormatter)

include(common.cmake)

file(GLOB INC_LOCAL *.h)
file(GLOB SRC_LOCAL *.cpp)
file(GLOB C_SRC_LOCAL *.c)
  
add_executable(TestCustomFormatter ${SRC_LOCAL} ${C_SRC_LOCAL} ${INC_LOCAL})

find_package(fmt CONFIG REQUIRED)
target_link_libraries(TestCustomFormatter PRIVATE fmt::fmt)  


