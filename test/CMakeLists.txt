include(../CMakeDefinitions.txt)
include_directories(..)

set(EXECUTABLES
	math
	enumerator
	bitflags
	infinite
	lambda
	logical
	node
	property
)
foreach (executable IN ITEMS ${EXECUTABLES})
	create_exec_test(${executable})
endforeach()
set_property(
	TARGET ${EXECUTABLES}
	PROPERTY COMPILE_DEFINITIONS "FALCON_GROUP_TEST"
)

add_subdirectory(algorithm)
add_subdirectory(bit)
add_subdirectory(container)
add_subdirectory(coordinates)
add_subdirectory(functional)
add_subdirectory(iostreams)
add_subdirectory(iterator)
add_subdirectory(memory)
add_subdirectory(parameter)
add_subdirectory(range)
add_subdirectory(templates)
add_subdirectory(tree)
add_subdirectory(tuple)
add_subdirectory(type_traits)
add_subdirectory(utility)
add_subdirectory(preprocessor)
add_subdirectory(string)
add_subdirectory(sfinae)
