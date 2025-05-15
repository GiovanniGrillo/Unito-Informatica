# Makefile for ex4/4.1

# Compiler and flags
JAVAC = javac
JAVA = java
RM = rm -f

# Source files
SOURCES = Lexer.java NumberTok.java Parser.java Tag.java Token.java Valutatore.java Word.java

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
