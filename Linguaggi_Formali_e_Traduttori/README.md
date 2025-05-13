# Linguaggi Formali e Traduttori - Esercizi e Materiale

Questo repository raccoglie il progetto per il corso di Linguaggi Formali e Traduttori dell'Università degli Studi di Torino, relativo all'anno accademico 2023/2024. Ogni cartella rappresenta una serie di esercizi o progetti svolti durante il corso, principalmente in Java, con l'obiettivo di approfondire la teoria e la pratica dei linguaggi formali, dei parser e dei traduttori. Il progetto di laboratorio di riferimento è descritto nel file PDF "LFT_Progetto_Lab.pdf".

## Struttura del repository

- **ex1/**: Primi esercizi introduttivi, con file sorgente Java e MakeFile per la compilazione.
- **ex2/**: Esercizi suddivisi in sottocartelle (2.1, 2.2, 2.3), ciascuna con lexer, token, e altri file Java utili per l'analisi lessicale. Ogni sottocartella contiene un MakeFile per la compilazione e file di esempio.
- **ex3/**: Esercizi avanzati su lexer e parser, suddivisi in 3.1 e 3.2, con Makefile, file Java e file di esempio (.lft).
- **ex4/**: Ulteriori esercizi su parser e valutatori, con file Java e dati di input.
- **ex5/**: Esercizi su traduttori e code generation, con file Java, esempi di input e output, e la libreria jasmin.jar per la generazione di bytecode.
- **LFT_Progetto_Lab.pdf**: Documento PDF con il progetto di laboratorio o materiale di riferimento per l'anno accademico 2023/2024.

## Compilazione ed esecuzione

Per compilare ed eseguire i programmi, entrare nella cartella dell'esercizio desiderato e utilizzare il comando `make` (o `make run` dove disponibile). Ad esempio:

```sh
cd ex3/3.2
make
make run
```

Per pulire i file compilati:

```sh
make clean
```

## Requisiti
- Tutti i programmi sono scritti in Java e richiedono il JDK installato.
- Alcuni esercizi utilizzano file di input di esempio (come file .lft o .txt).
- La struttura delle cartelle segue la suddivisione degli esercizi del corso.

## Note
Per domande o chiarimenti, fare riferimento al materiale del corso o contattare il docente.