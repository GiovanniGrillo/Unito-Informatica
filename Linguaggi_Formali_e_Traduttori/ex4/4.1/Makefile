all: valutatore

valutatore: Valutatore.class

%.class: %.java
	javac $<

Valutatore.class: Valutatore.java Lexer.class Tag.class Token.class Word.class NumberTok.class Parser.class

run: Valutatore.class
	java Valutatore

clean:
	rm -f *.class

.PHONY: all valutatore run clean