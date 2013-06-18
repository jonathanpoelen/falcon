#!/bin/sh

cd ~/projects/falcon/test

find -maxdepth 1 -type d | grep -Ev '^\.$|\.svn$' | sed s'/\.\///' \
| while read p
do
	echo 'include(../../CMakeDefinitions.txt)
include_directories(.. ../..)
' #> $l/CMakeLists.txt
	cd "$p"
	for f in $(ls *\.cpp)
	do
		name=${f%.cpp}
		echo add_executable'('$p'_'$name $f')' #>> "$p"/CMakeLists.txt
		echo "\n"FALCON_TEST_TO_MAIN'('$name'_test)' #>> "$f"
		done
	cd ..
done
