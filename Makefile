CFLAGS = -Wvla -Wextra -Werror -D_GNU_SOURCE
PROGRAMS = atomo alimentatore attivatore inibitore master ipcs exe
LIB = lib/

all: $(PROGRAMS)

# Programs compilation
atomo: atomo.c lib_atomo.o lib_header.o
	gcc atomo.c -o atomo $(CFLAGS)

alimentatore: alimentatore.c lib_alimentatore.o lib_header.o
	gcc alimentatore.c -o alimentatore $(CFLAGS)

attivatore: attivatore.c lib_attivatore.o lib_header.o
	gcc attivatore.c -o attivatore $(CFLAGS)

inibitore: inibitore.c lib_inibitore.o lib_header.o
	gcc inibitore.c -o inibitore $(CFLAGS)

master: master.c lib_master.o lib_header.o
	gcc master.c -o master $(CFLAGS)

#Library compilation
lib_header.o: $(LIB)lib_header.c $(LIB)resources.h
	gcc -c $(LIB)lib_header.c -o $(LIB)lib_header.o $(CFLAGS)

lib_atomo.o: $(LIB)lib_atomo.c $(LIB)resources.h
	gcc -c $(LIB)lib_atomo.c -o $(LIB)lib_atomo.o $(CFLAGS)

lib_master.o: $(LIB)lib_master.c $(LIB)resources.h
	gcc -c $(LIB)lib_master.c -o $(LIB)lib_master.o $(CFLAGS)

lib_alimentatore.o: $(LIB)lib_alimentatore.c $(LIB)resources.h
	gcc -c $(LIB)lib_alimentatore.c -o $(LIB)lib_alimentatore.o $(CFLAGS)

lib_inibitore.o: $(LIB)lib_inibitore.c $(LIB)resources.h
	gcc -c $(LIB)lib_inibitore.c -o $(LIB)lib_inibitore.o $(CFLAGS)

lib_attivatore.o: $(LIB)lib_attivatore.c $(LIB)resources.h
	gcc -c $(LIB)lib_attivatore.c -o $(LIB)lib_attivatore.o $(CFLAGS)

ipcs:
	@ipcrm -a
	@clear

exe:
	./master

clean:
	rm -f *.o atomo alimentatore attivatore inibitore master
	rm -f $(LIB)*.o