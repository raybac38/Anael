CC=gcc

CFLAG= -O0 -Wall -g -Wextra -I./include -I./raylib/src
CLIBS= -lraylib -lm -ldl -lpthread -lGL

SRC_DIR= ./src/
BIN_DIR= ./bin/
INC_DIR= ./include/ ./raylib/src
LIB_DIR= ./raylib/src

SRC := $(wildcard $(SRC_DIR)*.c)

OBJ := $(patsubst $(SRC_DIR)%.c, $(BIN_DIR)%.o, $(SRC))

EXEC= main

all: set_up $(EXEC) 

$(EXEC): $(OBJ)
	$(CC) $(CFLAG) -o $@ $^ -L$(LIB_DIR) $(CLIBS)

$(BIN_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAG) -c -I$(INC_DIR) -o $@ $^
	
clean:
	-@rm -r $(BIN_DIR)
	-@rm $(EXEC)
	@echo "cleanup completed"

init:
	-mkdir $(BIN_DIR) $(SRC_DIR) $(INC_DIR)

set_up:
	-mkdir $(BIN_DIR)
	
debug:
	echo $(SRC)
	echo $(OBJ)

.PHONY: clean set_up

