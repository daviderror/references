TARGET ?= max
SRC := src/main.c src/mylib.c
CC = gcc
CFLAGC := -O2 -std=gnu11 -fms-extensions

.PHONY: clean tidy

$(TARGET): $(SRC:.c=.o)
	$(CC) $(CFLAGC) $^ -o $@

clean:
	rm -f $(SRC:.c=.o)

tidy: clean
	rm -f $(TARGET)