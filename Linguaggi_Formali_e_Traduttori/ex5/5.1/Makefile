all: translator

translator: Translator.class

%.class: %.java
	javac $<

Translator.class: Translator.java Lexer.class Tag.class Token.class Word.class NumberTok.class Parser.class SymbolTable.class CodeGenerator.class Instruction.class OpCode.class

run: Translator.class
	java Translator

clean:
	rm -f *.class Output.j

.PHONY: all translator run clean