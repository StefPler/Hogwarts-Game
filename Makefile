CC=g++
SRC=src/WizardingDuel.cpp
LIB=libs/Hogwarts.h
BIN=WizardingDuel
CFLAGS=-std=c++11

game: $(SRC) $(LIB)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -rf $(BIN)