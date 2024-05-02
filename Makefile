all: prova

prova: clear atomo alimentatore attivatore test2

test: test.c
	gcc test.c -o test -Wvla -Wextra -Werror -w
	ipcrm -a

test2: test2.c
	gcc test2.c -o test2 -Wvla -Wextra -Werror -w
	./test2

atomo: atomo.c
	gcc atomo.c -o atomo -Wvla -Wextra -Werror -w

atomo2: atomo2.c
	gcc atomo2.c -o atomo2 -Wvla -Wextra -Werror -w

attivatore: attivatore.c
	gcc attivatore.c -o attivatore -Wvla -Wextra -Werror -w

alimentatore: alimentatore.c
	gcc alimentatore.c -o alimentatore -Wvla -Wextra -Werror -w

clear:
	rm -f test2 atomo attivatore alimentatore