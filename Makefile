all: PROGETTO
PROGETTO: Prova
Prova_make : Prova
	gcc -Wpedantic Prova.c -o Prova -w
clean:
	rm -f Master Giornaliera Movimento Maelstrom 