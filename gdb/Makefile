TARGET ?= max
SRC := main.c mylib.c
CC = gcc
CFLAGC := -O2 -g3 -std=gnu11 -Wall -Wextra -Wpedantic -fms-extensions
LDFLAGS := -ldl -lm -Wl
BUILDDIR := .build
SRCDIRS := src
INCDIRS := inc

.PHONY: all clean tidy

all: $(BUILDDIR)/$(TARGET)

$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
	$(CC) $(CFLAGC) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIRS)/%.c $(BUILDDIR)
	$(CC) $(CFLAGC) -DA=6 -DB=7 -DDEBUG=0 $(addprefix -I,$(INCDIRS)) -c $< -o $@

clean:
	rm -f $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))

tidy: clean
	rm -rf $(BUILDDIR)