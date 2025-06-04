all: lexer

lexer: Lexer.class

%.class: %.java
	javac $<

Lexer.class: Lexer.java Tag.class Token.class Word.class NumberTok.class

run: Lexer.class
	java Lexer

clean:
	rm -f *.class