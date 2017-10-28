.PHONY: all clean

SOURCES_DIR = sources

all: main.o qsort.o filefuncs.o
	gcc -o sorter main.o qsort.o filefuncs.o

clean:
	rm -rf sorter *.o

main.o: $(SOURCES_DIR)/main.c
	gcc -c -o main.o $(SOURCES_DIR)/main.c

qsort.o: $(SOURCES_DIR)/qsort.c
	gcc -c -o qsort.o $(SOURCES_DIR)/qsort.c

filefuncs.o: $(SOURCES_DIR)/filefuncs.c
	gcc -c -o filefuncs.o $(SOURCES_DIR)/filefuncs.c
