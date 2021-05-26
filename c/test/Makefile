CC = gcc
DEPS = ./test.o \
				../src/utils.o \
				../src/wrap.o \
				../src/solve.o \
				../src/operation.o
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
