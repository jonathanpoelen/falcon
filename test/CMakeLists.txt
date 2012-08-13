include(../CMakeDefinitions.txt)
include_directories(..)

set(EXECUTABLES
	math
	enumerator
	flag
	infinite
	lambda
	logical
	node
)
foreach (executable IN ITEMS ${EXECUTABLES})
	create_exec_test(${executable})
endforeach()
set_property(
	TARGET ${EXECUTABLES}
	PROPERTY COMPILE_DEFINITIONS "FALCON_GROUP_TEST"
)

add_subdirectory(algorithm)
add_subdirectory(arg)
add_subdirectory(bit)
add_subdirectory(container)
add_subdirectory(functional)
add_subdirectory(iostream)
add_subdirectory(istream)
add_subdirectory(iterator)
add_subdirectory(java_iterator)
add_subdirectory(memory)
add_subdirectory(ostream)
add_subdirectory(templates)
add_subdirectory(tree)
add_subdirectory(tuple)
add_subdirectory(type_traits)
add_subdirectory(utility)
add_subdirectory(parameter)
add_subdirectory(range)
add_subdirectory(coordinates)