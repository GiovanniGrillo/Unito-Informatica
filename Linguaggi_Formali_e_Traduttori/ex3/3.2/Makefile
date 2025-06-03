all: parser

parser: Parser.class

%.class: %.java
	javac $<

Parser.class: Parser.java Lexer.class Tag.class Token.class Word.class NumberTok.class

Lexer.class: Lexer.java Tag.class Token.class Word.class NumberTok.class

run: Parser.class
	java Parser

test: Parser.class
	java Parser

clean:
	rm -f *.class

.PHONY: all parser run test clean