CC = gcc
CFLAGS = -Wvla -Wextra -Werror -D_GNU_SOURCE
PROGRAMS = atomo alimentatore attivatore inibitore master ipcs exe

all: $(PROGRAMS)

# Compilazione dei programmi
atomo: atomo.c lib_atomo.o lib_header.o
	$(CC) $(CFLAGS) -o atomo atomo.c

alimentatore: alimentatore.c lib_alimentatore.o lib_header.o
	$(CC) $(CFLAGS) -o alimentatore alimentatore.c

attivatore: attivatore.c lib_attivatore.o lib_header.o
	$(CC) $(CFLAGS) -o attivatore attivatore.c

inibitore: inibitore.c lib_inibitore.o lib_header.o
	$(CC) $(CFLAGS) -o inibitore inibitore.c

master: master.c lib_master.o lib_header.o
	$(CC) $(CFLAGS) -o master master.c

# Compilazione delle librerie
lib_header.o: lib_header.c resources.h
	$(CC) $(CFLAGS) -c lib_header.c

lib_atomo.o: lib_atomo.c resources.h
	$(CC) $(CFLAGS) -c lib_atomo.c

lib_master.o: lib_master.c resources.h
	$(CC) $(CFLAGS) -c lib_master.c

lib_alimentatore.o: lib_alimentatore.c resources.h
	$(CC) $(CFLAGS) -c lib_alimentatore.c

lib_inibitore.o: lib_inibitore.c resources.h
	$(CC) $(CFLAGS) -c lib_inibitore.c

lib_attivatore.o: lib_attivatore.c resources.h
	$(CC) $(CFLAGS) -c lib_attivatore.c

ipcs:
	@clear
	@ipcrm -a

exe:
	./master

clean:
	rm -f *.o ./master ./atomo ./alimentatore ./attivatore ./inibitore
