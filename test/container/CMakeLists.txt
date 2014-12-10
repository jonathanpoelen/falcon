include(../../CMakeDefinitions.txt)
include_directories(.. ../..)

create_exec_test(container_view)
create_exec_test(range_access_traits)
create_exec_test(indirect_container)
create_exec_test(ptr_container)
create_exec_test(zone_access)
create_exec_test(unordered_container_view)
