#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                      makes Sparse
#  make MatrixClient         makes MatrixClient
#  make MatrixTest           makes MatrixTest
#  make clean                removes all binaries
#  make checkMatrixClient    runs MatrixClient under valgrind
#  make checkMatrixTest      runs MatrixTest under valgrind
#  make checkSparse          runs Sparse under valgrind on in8
#------------------------------------------------------------------------------

MAIN           = Sparse
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).c

TEST           = MatrixClient
TESTOBJ        = $(TEST).o
TESTSRC        = $(TEST).c

TEST2          = MatrixTest
TEST2OBJ       = $(TEST2).o
TEST2SRC       = $(TEST2).c

ADT1           = Matrix
ADT1OBJ        = $(ADT1).o
ADT1SRC        = $(ADT1).c
ADT1_H         = $(ADT1).h

ADT2           = List
ADT2OBJ        = $(ADT2).o
ADT2SRC        = $(ADT2).c
ADT2_H         = $(ADT2).h

COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

INFILE         = in8
OUTFILE        = myout8

#------------------------------------------------------------------------------
# Default target
#------------------------------------------------------------------------------
all: $(MAIN)

#------------------------------------------------------------------------------
# Build rules
#------------------------------------------------------------------------------
$(MAIN): $(MAINOBJ) $(ADT1OBJ) $(ADT2OBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADT1OBJ) $(ADT2OBJ)

$(MAINOBJ): $(MAINSRC) $(ADT1_H)
	$(COMPILE) $(MAINSRC)

$(TEST): $(TESTOBJ) $(ADT1OBJ) $(ADT2OBJ)
	$(LINK) $(TEST) $(TESTOBJ) $(ADT1OBJ) $(ADT2OBJ)

$(TESTOBJ): $(TESTSRC) $(ADT1_H)
	$(COMPILE) $(TESTSRC)

$(TEST2): $(TEST2OBJ) $(ADT1OBJ) $(ADT2OBJ)
	$(LINK) $(TEST2) $(TEST2OBJ) $(ADT1OBJ) $(ADT2OBJ)

$(TEST2OBJ): $(TEST2SRC) $(ADT1_H)
	$(COMPILE) $(TEST2SRC)

$(ADT1OBJ): $(ADT1SRC) $(ADT1_H) $(ADT2_H)
	$(COMPILE) $(ADT1SRC)

$(ADT2OBJ): $(ADT2SRC) $(ADT2_H)
	$(COMPILE) $(ADT2SRC)

#------------------------------------------------------------------------------
# Cleanup
#------------------------------------------------------------------------------
clean:
	$(REMOVE) $(MAIN) $(MAINOBJ) \
	          $(TEST) $(TESTOBJ) \
	          $(TEST2) $(TEST2OBJ) \
	          $(ADT1OBJ) $(ADT2OBJ)

#------------------------------------------------------------------------------
# Valgrind checks
#------------------------------------------------------------------------------
check$(MAIN): $(MAIN)
	$(MEMCHECK) ./$(MAIN) $(INFILE) $(OUTFILE)

check$(TEST): $(TEST)
	$(MEMCHECK) ./$(TEST)

check$(TEST2): $(TEST2)
	$(MEMCHECK) ./$(TEST2)

#------------------------------------------------------------------------------
# ADT-only targets
#------------------------------------------------------------------------------
list: $(ADT2OBJ)

matrix: $(ADT1OBJ)

checklist:
	$(COMPILE) -fsyntax-only $(ADT2SRC)

checkmatrix:
	$(COMPILE) -fsyntax-only $(ADT1SRC)
