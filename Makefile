CC=g++
SRC=WizardingDuel.cpp
LIB=Hogwarts.h
BIN=WizardingDuel
CFLAGS=-std=c++11

game: $(SRC) $(LIB)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -rf $(BIN)