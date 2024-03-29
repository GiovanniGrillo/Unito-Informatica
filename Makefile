all: PROGETTO
PROGETTO: Giornaliera_make Atomo_make Attivatore_make Master_make
Master_make: Master
	gcc -Wpedantic -w  Master.c -o Master
Giornaliera_make: Giornaliera 
	gcc -Wpedantic -w  Giornaliera.c  -o Giornaliera
Movimento_make:Movimento
	gcc -Wpedantic -w  Movimento.c    -o Movimento
Maelstrom_make : Maelstrom
	gcc -Wpedantic -w  Maelstrom.c    -o Maelstrom
clean:
	rm -f Master Giornaliera Movimento Maelstrom 