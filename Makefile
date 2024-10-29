all: clear alimentatore attivatore atomo inibitore master

alimentatore: alimentatore.c
	gcc alimentatore.c -o alimentatore -Wvla -Wextra

attivatore: attivatore.c
	gcc attivatore.c -o attivatore -Wvla -Wextra -Werror

atomo: atomo.c
	gcc atomo.c -o atomo -Wvla -Wextra -Werror

inibitore: inibitore.c
	gcc inibitore.c -o inibitore -Wvla -Wextra

master: master.c
	gcc master.c -o master -Wvla -Wextra -Werror
	ipcrm -a
	./master

clear:
	rm -f alimentatore attivatore atomo inibitore master