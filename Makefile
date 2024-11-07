CC = gcc
CFLAGS = -Wvla -Wextra -Werror -D_GNU_SOURCE
PROGRAMS = atomo alimentatore attivatore inibitore master ipcs exe

all: $(PROGRAMS)

# Compilazione dei programmi
atomo: atomo.c lib_atomo.o lib_header.o
	$(CC) $(CFLAGS) -o atomo atomo.c

alimentatore: alimentatore.c lib_alimentatore.o lib_header.o
	$(CC) $(CFLAGS) -o alimentatore alimentatore.c

attivatore: attivatore.c lib_header.o
	$(CC) $(CFLAGS) -o attivatore attivatore.c

inibitore: inibitore.c lib_header.o
	$(CC) $(CFLAGS) -o inibitore inibitore.c

master: master.c lib_master.o lib_header.o
	$(CC) $(CFLAGS) -o master master.c

# Compilazione delle librerie
lib_header.o: lib_header.c
	$(CC) $(CFLAGS) -c lib_header.c

lib_atomo.o: lib_atomo.c
	$(CC) $(CFLAGS) -c lib_atomo.c

lib_master.o: lib_master.c
	$(CC) $(CFLAGS) -c lib_master.c

lib_alimentatore.o: lib_alimentatore.c
	$(CC) $(CFLAGS) -c lib_alimentatore.c

ipcs:
	@ipcrm -a

exe:
	@./master

clean:
	rm -f *.o ./master ./atomo ./alimentatore ./attivatore ./inibitore
