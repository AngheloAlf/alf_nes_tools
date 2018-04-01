C_LIBS   := c_libs
SRC      := src
S_C_LIBS := $(SRC)/$(C_LIBS)
OBJ      := obj
O_C_LIBS := $(OBJ)/$(C_LIBS)
OUT      := out
LIBS     := 
CFLAGS   := -Wall
CC       := gcc
BINARY   := exe
RESOURCE := resource

SOURCES  := $(wildcard $(S_C_LIBS)/*.c)
OBJECTS  := $(patsubst $(S_C_LIBS)/%.c, $(O_C_LIBS)/%.o, $(SOURCES))
BINARIES := $(wildcard $(SRC)/*.c)
B_OBJECTS:= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(BINARIES))
FINAL    := $(patsubst $(SRC)/%.c, %, $(BINARIES))

# all: $(OBJECTS)
# 	$(CC) $^ -o $@

all: $(B_OBJECTS) $(OBJECTS) $(FINAL)

$(FINAL): %: $(OBJECTS)
	$(CC) -I$(OBJ) -I$(O_C_LIBS) $(OBJECTS) $(OBJ)/$@.o -o $(OUT)/$@ $(CFLAGS) $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) -o $@ -c $< $(CFLAGS) $(LIBS)

$(O_C_LIBS)/%.o: $(S_C_LIBS)/%.c
	$(CC) -I$(S_C_LIBS) -o $@ -c $< $(CFLAGS) $(LIBS)


clean:
	rm $(OBJECTS) $(B_OBJECTS)
