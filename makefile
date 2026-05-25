	CC = gcc
CFLAGS = -Wall -g

TARGET = inverted_search

SRC = main.c inverted_ser.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

