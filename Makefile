all: clear alimentatore attivatore atomo inibitore master

alimentatore: alimentatore.c
	gcc alimentatore.c -o alimentatore -Wvla -Wextra -Werror -w

attivatore: attivatore.c
	gcc attivatore.c -o attivatore -Wvla -Wextra -Werror -w

atomo: atomo.c
	gcc atomo.c -o atomo -Wvla -Wextra -Werror -w

inibitore: inibitore.c
	gcc inibitore.c -o inibitore -Wvla -Wextra -w

master: master.c
	gcc master.c -o master -Wvla -Wextra -Werror -w
	ipcrm -a
	./master

clear:
	rm -f alimentatore attivatore atomo inibitore master