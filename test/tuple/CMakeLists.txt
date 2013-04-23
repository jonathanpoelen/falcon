include(../../CMakeDefinitions.txt)
include_directories(.. ../..)

create_exec_test(tuple_apply)
create_exec_test(tuple_compose)
create_exec_test(to_tuple_pointer)
create_exec_test(to_tuple_reference)
create_exec_test(parameter_pack)
create_exec_test(tuple_for_each)
