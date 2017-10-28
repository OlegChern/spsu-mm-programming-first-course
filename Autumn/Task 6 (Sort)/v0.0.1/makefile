.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects

all: main qsort
	gcc -o sorter $(OBJECTS_DIR)/main.o $(OBJECTS_DIR)/qsort.o

clean:
	rm -rf sorter $(OBJECTS_DIR)

objects_dir:
	mkdir -p $(OBJECTS_DIR)
	
main: $(SOURCES_DIR)/main.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

qsort: $(SOURCES_DIR)/qsort.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o