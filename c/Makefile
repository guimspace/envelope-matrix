CC = gcc
DEPS = test.o tools.o wrap.o solve.o
TARGET = envelope


$(TARGET): $(DEPS)
	$(CC) $(DEPS) -o $(TARGET)

all:
	$(TARGET)

test:
	make clean
	make
	./envelope



.SILENT:
.PHONY:  lint clean

clean:
	-rm -rf $(DEPS)
	-rm -rf $(TARGET)
