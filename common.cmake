cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)

set(PLATFORM_DIR ${CMAKE_SYSTEM_NAME})
set(SOLUTION_ROOT ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(THIRD_PARTY_PATH ${SOLUTION_ROOT}/third_party)
#option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

include_directories(${SOLUTION_ROOT}/Include)
include_directories(${SOLUTION_ROOT}/Source)
include_directories(${THIRD_PARTY_PATH})

#link_directories(${SOLUTION_ROOT}/third_party)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SOLUTION_ROOT}/_lib_/${CMAKE_BUILD_TYPE}/${PLATFORM_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SOLUTION_ROOT}/_lib_/${CMAKE_BUILD_TYPE}/${PLATFORM_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SOLUTION_ROOT}/_bin_/${CMAKE_BUILD_TYPE}/${PLATFORM_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTESIONS ON)

#set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
if (WIN32)
	add_compile_options(
		#/W4 
		/WX
		/EHsc
		#/DEBUG
	)

	add_definitions(
		-D_CRT_SECURE_NO_WARNINGS
		-D_SCL_SECURE_NO_WARNINGS
		-DNOMINMAX=1
		-DNOGDI
	)

else(WIN32)

	set(CMAKE_CXX_FLAGS_RELEASE "-O3")

	add_definitions(
		-D__STDC_WANT_DEC_FP__ 
	)

	add_compile_options(
		-gdwarf-4
		-Wall
		-Wextra
		#-pedantic 
		#-Werror
	)

	add_link_options(
		-static-libstdc++
		-static-libgcc
		-pthread
	)
endif(WIN32)
