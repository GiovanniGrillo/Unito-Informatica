CC = gcc
CFLAGS = -Wvla -Wextra -Werror -D_GNU_SOURCE -g
PROGRAMS = atomo alimentatore attivatore inibitore master ipcs exe

all: $(PROGRAMS)

atomo: atomo.c
	$(CC) $(CFLAGS) -o atomo atomo.c

alimentatore: alimentatore.c
	$(CC) $(CFLAGS) -o alimentatore alimentatore.c

attivatore: attivatore.c
	$(CC) $(CFLAGS) -o attivatore attivatore.c

inibitore: inibitore.c
	$(CC) $(CFLAGS) -o inibitore inibitore.c

master: master.c
	$(CC) $(CFLAGS) -o master master.c

ipcs:
	ipcrm -a

exe:
	./master

clean:
	rm -f ./master ./atomo ./alimentatore ./attivatore ./inibitore
