include(../../CMakeDefinitions.txt)
include_directories(.. ../..)

create_exec_test(is_ios)
create_exec_test(iomanip)
create_exec_test(multibuf)
create_exec_test(set_contents_file)
