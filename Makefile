# Makefile

################################################################
# File dependencies for the Kestrel compiler                   #
# Author:  Douglas Jones                                       #
# Date:    8/29/2016 -- created                                #
# Date:    9/9/2016  -- incorporate stringpool & related       #
# Date:    9/23/2016 -- incorporate keywords & related         #
#                                                              #
# Instructions:                                                #
#          make         -- will build compiler someday         #
#          make testlex -- build lexical analysis test program #
#          make tester  -- build tester that runs all tests    #
#          make clean   -- delete everything unnecessary       #
################################################################

#######
# configuration options

# compiler to use, may give global compiler options here  
COMPILER = c++
CFLAGS = -c -g
####
# Compile all files to object files
%.o : %.c
	$(COMPILER) $(CFLAGS) $< -o $@

#######
# primary make target:  the Kestrel compiler

KESTREL_O = main.o lexical.o lexsupport.o keywords.o symboltable.o stringpool.o \
				log.o program.o block.o declaration.o statement.o \
				environment.o expression.o reference.o type.o CodeGen.o

kestrel: $(KESTREL_O)
	$(COMPILER) -o kestrel $(KESTREL_O)


#######
# secondary make target: testlex for testing lexical.o

TESTLEX_O = testlex.o lexical.o keywords.o symboltable.o stringpool.o log.o

testlex: $(TESTLEX_O)
	$(COMPILER) -o testlex $(TESTLEX_O)


#######
# secondary make target: tester

TESTER_O = lexical.o lexsupport.o keywords.o symboltable.o stringpool.o \
				log.o program.o block.o declaration.o statement.o reference.o type.o\
				environment.o expression.o CodeGen.o tests/tester.o tests/testLexer.o \
				tests/testSymbolTable.o tests/testStringPool.o tests/testStatement.o \
				tests/testExpression.o tests/testlinklst.o tests/testCodeGen.o

tester: $(TESTER_O)
	$(COMPILER) -o tester $(TESTER_O)

#######
# secondary make target: all for making all targets

.PHONY: all
all: kestrel testlex tester

#######
# secondary make target:  clean for cleaning up the project

clean:
	-@rm -f *.o
	-@rm -f tests/*.o
	-@rm -f testlex
	-@rm -f kestrel
	-@rm -f tester
	-@echo "Successfully cleaned"
