all: PROGETTO

PROGETTO: Prova

Prova: test test2 atomo atomo2 attivatore alimentatore

test: test.c
	gcc test.c -o test -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "-----Eseguo test2-----"
	@./test2

test2: test2.c
	gcc test2.c -o test2 -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "-----Eseguo test2-----"
	@./test2

atomo: atomo.c
	gcc atomo.c -o atomo -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "<-----Devi eseguire atomo----->"
	# @./atomo

atomo2: atomo2.c
	gcc atomo2.c -o atomo2 -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "<-----Devi eseguire atomo2----->"
	# @./atomo2

attivatore: attivatore.c
	gcc attivatore.c -o attivatore -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "<-----Devi eseguire attivatore----->"
	# @./attivatore

alimentatore: alimentatore.c
	gcc alimentatore.c -o alimentatore -w
	@echo "Faccio ipcrm -a"
	ipcrm -a
	@echo "Eseguo alimentatore"
	@./alimentatore

c:
	@echo "Rimuovo gli eseguibili:"
	rm -f test test2 atomo atomo2 attivatore alimentatore

.PHONY: all clean