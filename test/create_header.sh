#/bin/sh
for f in $*; do
	dir=$(dirname "$f")
	base=$(basename "$f" cpp)
	if [ "$dir" != '.' ]; then
		base=$dir/$base
	fi
	m=${base^^*}
	m=${m:0:-1}
	m=FALCON_TEST_${m/\//_}_HPP
	echo "#ifndef $m
#define $m

"$(cat $f \
| grep -Ev '^\*\*|\;|=|\|"|\!|\?|if \(|#|\{|\}|/|struct |class ' \
| grep -E '^[_a-zA-Z]|([_a-zA-Z] [*_a-zA-Z])' \
| sed s/\)$/\)\;/)"

#endif //$m" > $base''hpp
done
