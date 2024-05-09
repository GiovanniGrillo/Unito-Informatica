all: clear atomo alimentatore attivatore inibitore

test2: test2.c
	gcc test2.c -o test2 -Wvla -Wextra -Werror -w
	ipcrm -a
	./test2

atomo: atomo.c
	gcc atomo.c -o atomo -Wvla -Wextra -Werror -w
	gcc test2.c -o test2 -Wvla -Wextra -Werror -w

attivatore: attivatore.c
	gcc attivatore.c -o attivatore -Wvla -Wextra -Werror -w

alimentatore: alimentatore.c
	gcc alimentatore.c -o alimentatore -Wvla -Wextra -Werror -w

inibitore: inibitore.c
	gcc inibitore.c -o inibitore -Wvla -Wextra -w

clear:
	rm -f test2 atomo attivatore inibitore alimentatore