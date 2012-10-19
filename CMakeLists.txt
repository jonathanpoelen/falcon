project(falcon)

cmake_minimum_required(VERSION 2.8)

include(CMakeDefinitions.txt)
include_directories(.)

add_executable(falcon-test test.cpp)

add_subdirectory(test)

# add_subdirectory(falcon)

enable_testing()
# find test -type f -perm 775 | while read l ; do $l >/dev/null ; done |& grep -v \ passed

