project(falcon)

cmake_minimum_required(VERSION 2.8)

# if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	include(CMakeForceCompiler)
	CMAKE_FORCE_CXX_COMPILER(g++-4.7 GNU-4.7)
# endif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

include(CMakeDefinitions.txt)
include_directories(.)

add_executable(falcon-test test.cpp)

add_subdirectory(test)

# add_subdirectory(falcon)

enable_testing()
# find test -type f -perm 775 | while read l ; do $l >/dev/null ; done |& grep -v \ passed

