CC=mpicc
CFLAGS=-I. -Wall -g -fsanitize=address,leak
TARGET=node

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -o $@ $^
clean:
	rm $(TARGET)
