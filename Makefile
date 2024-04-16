all: PROGETTO

PROGETTO: Prova

Prova: test test2 atomo attivatore alimentatore

test: test.c
	gcc test.c -o test -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "Eseguo test2"
	@./test2

test2: test2.c
	gcc test2.c -o test2 -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "Eseguo test2"
	@./test2

atomo: atomo.c
	gcc atomo.c -o atomo -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "Eseguo atomo"
	@./atomo

attivatore: attivatore.c
	gcc attivatore.c -o attivatore -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "Eseguo attivatore"
	@./attivatore

alimentatore: alimentatore.c
	gcc alimentatore.c -o alimentatore -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "Eseguo alimentatore"
	@./alimentatore

clean:
	@echo "Rimuovo gli eseguibili:"
	rm -f test test2 atomo attivatore alimentatore

.PHONY: all clean
