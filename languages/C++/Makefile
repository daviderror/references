obj-m += main.o

CFLAGS = -O2 -std=gnu++2a -Wall -Wextra -Wpedantic
CFLAGS += $(shell pkg-config --cflags $(LIBS))

.PHONY: all

all:
	$(CXX) $(CFLAGS) src/main.cpp -pthread -o main
tidy_o:
	rm -f main
