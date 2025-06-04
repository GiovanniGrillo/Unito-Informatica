SOURCES = ex1_1.java \
          ex1_2.java \
          ex1_3.java \
          ex1_4.java \
          ex1_5.java \
          ex1_6.java

CLASSES = $(SOURCES:.java=.class)

all: $(CLASSES)

%.class: %.java
	javac $(JFLAGS) $<

clean:
	rm -f *.class

run1_1: ex1_1.class
	java ex1_1

run1_2: ex1_2.class
	java ex1_2

run1_3: ex1_3.class
	java ex1_3

run1_4: ex1_4.class
	java ex1_4

run1_5: ex1_5.class
	java ex1_5

run1_6: ex1_6.class
	java ex1_6

runall: run1_1 run1_2 run1_3 run1_4 run1_5 run1_6

test: all runall

.PHONY: all clean runall test run1_1 run1_2 run1_3 run1_4 run1_5 run1_6