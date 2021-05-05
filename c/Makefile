CC = gcc
DEPS = test.o envelope-tools.o envelope-wrap.o envelope-solve.o
TARGET = cTest


$(TARGET): $(DEPS)
	$(CC) $(DEPS) -o $(TARGET)

all:
	$(TARGET)

test:
	make clean
	make
	./cTest



.SILENT:
.PHONY:  lint clean

clean:
	-rm -rf $(DEPS)
	-rm -rf $(TARGET)
