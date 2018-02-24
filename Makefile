SRC      := src
OBJ      := obj
OUT      := out
LIBS     := 
CFLAGS   := -Wall
CC       := gcc
BINARY   := exe
RESOURCE := resource

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
BINARY := main

# all: $(OBJECTS)
# 	$(CC) $^ -o $@

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -I$(OBJ) $(OBJECTS) -o $(BINARY) $(CFLAGS) $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) -c $< -o $@ $(CFLAGS) $(LIBS)


clean:
	rm $(OBJECTS)
