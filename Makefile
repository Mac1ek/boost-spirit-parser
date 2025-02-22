PROG = parser
PARAM = -std=c++23 -Wall -pedantic
SRC1 = spirit_$(PROG).cpp
SRC2 = $(PROG)_adapt.cpp
OBJ1 = spirit_$(PROG).o
OBJ2 = $(PROG)_adapt.o

all: $(PROG) run

$(PROG): $(OBJ1) $(OBJ2)
	g++ -o $(PROG) $(OBJ1) $(OBJ2)

$(OBJ1): $(SRC1)
	g++ -c $(SRC1) $(PARAM) -o $(OBJ1)

$(OBJ2): $(SRC2)
	g++ -c $(SRC2) $(PARAM) -o $(OBJ2)

run: $(PROG)
	./$(PROG) test_pnr_parser.xml

clean:
	rm -f $(PROG) $(OBJ1) $(OBJ2)

