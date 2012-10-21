#/bin/sh
USAGE='[dirname] category'

cd `dirname $0`

[ $# = 0 ] && echo $0 $USAGE && exit 1

if [ $# = 2 ];then
	d=${1%%\/}
	shift 1
	defbase=$d'_'
	cmakelist=$d/CMakeLists.txt
	mmain=FALCON_TEST_TO_MAIN
	if [ ! -d $d ];then
		[ -e $d ] && echo $d is not directory && exit 3
		mkdir $d
		echo "include(../../CMakeDefinitions.txt)
include_directories(.. ../..)
" > $cmakelist
	fi
else
	d=
	defbase=
	cmakelist=CMakeLists.txt
	mmain=FALCON_GROUP_TEST_TO_MAIN
fi

h="$d/$1.hpp"
s="$d/$1.cpp"
( [ -e $h ] && echo $h exists || [ -e $s ] && echo $s exists ) && exit 2

def=$defbase$1
#with bash: ${def^^*}, with zsh: $def:u
def=FALCON_TEST_$(echo $def | tr -s '[a-z]' '[A-Z]')_HPP

echo "#ifndef $def
#define $def

void $1_test();

#endif" > $h

echo "#include <test/test.hpp>
#include <falcon/$h>
#include \"$1.hpp\"

void $1_test()
{

}

$mmain($1_test)" > $s

echo create_exec_test"($1)" >> $cmakelist

exit 0
