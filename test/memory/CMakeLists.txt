include(../../CMakeDefinitions.txt)
include_directories(.. ../..)

create_exec_test(new)
create_exec_test(static_new)
create_exec_test(stack_allocator)
create_exec_test(range_allocator)
