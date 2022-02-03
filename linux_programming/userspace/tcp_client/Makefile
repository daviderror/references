.PHONY: all clean
TARGET = client

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c -lreadline

all: $(TARGET)

clean:
	-rm -rf *.o
	-rm -rf $(TARGET)
