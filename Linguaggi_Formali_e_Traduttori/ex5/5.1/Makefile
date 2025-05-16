# Makefile for ex5/5.1

# Compiler and flags
JAVAC = javac
JAVA = java
RM = rm -f

# Source files
SOURCES = CodeGenerator.java Instruction.java Lexer.java NumberTok.java OpCode.java Parser.java SymbolTable.java Tag.java Token.java Translator.java Word.java

# Class files
CLASSES = $(SOURCES:.java=.class)

# Default target
all: $(CLASSES)

# Rule to compile .java files to .class files
%.class: %.java
	$(JAVAC) $<

# Clean target
clean:
	$(RM) $(CLASSES)