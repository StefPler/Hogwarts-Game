CC=g++
SRC=WizardingDuel.cpp
LIB=Hogwarts.h
BIN=WizardingDuel

game: $(SRC) $(LIB)
	$(CC) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -rf $(BIN)