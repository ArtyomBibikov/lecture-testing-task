cmake_minimum_required(VERSION 3.10)
project(stack)

option(ENABLE_SANITIZERS ON)
option(ENABLE_ANALYZER ON)

add_library(stack stack.c)

add_executable(main main.c)
target_link_libraries(main stack)

add_executable(tests tests.c)
target_link_libraries(tests stack)

add_executable(benchmarks benchmarks.c)
target_link_libraries(benchmarks stack)

add_compile_options(/W4 /WX /analyze)

set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()