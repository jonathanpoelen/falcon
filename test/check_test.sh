#!/bin/bash
find "$(dirname $0)"/../build/test -type f -perm 775 \
| while read l ;
	do $l >/dev/null
	[ $? != '0' ] && echo -e '\033[31m'$l'\033[00m' >&2
done \
|& grep -v \ passed
