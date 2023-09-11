#!/bin/bash

assert() {
    printf '%-30s:' "\"$1\""

    echo -n -e "$1" | bash >cmp >&-
    expected=$?

    echo -n -e "$1" | ./minishell >out >&-
    actual=$?

    diff cmp out >/dev/null && echo -n -e '  diff \033[0;32mOK\033[0;37m' || echo -n -e '  diff \033[0;31mNG\033[0;37m'

    if [ "$actual" = "$expected" ]; then
        echo -n -e '  status \033[0;32mOK\033[0;37m\n'
    else
        echo -n -e "  status \033[0;31mNG\033[0;37m, expected $expected but got $actual\n"
    fi
    echo 
    rm out cmp
}

#$
assert "ls -l"
