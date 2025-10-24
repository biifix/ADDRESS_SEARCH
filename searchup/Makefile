CC = gcc
CFLAGS = -Wall -g

SRC := \
    main.c \
    dict.c \
    list.c \
    record.c \
    result.c \
    ptrie.c \
    bit.c

OBJ := $(SRC:.c=.o)

EXE = dict2

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDLIBS)


clean:
	rm -f $(OBJ) $(EXE)
