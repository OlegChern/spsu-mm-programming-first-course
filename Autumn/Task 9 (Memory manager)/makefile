.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = memory_manager

all: objects_dir main memory_manager bigint
	gcc $(OBJECTS_DIR)/*.o -o $(EXE_NAME) -lm

clean:
	rm -rf $(EXE_NAME) $(OBJECTS_DIR)

objects_dir:
	mkdir -p $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

memory_manager: $(SOURCES_DIR)/memory_manager.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

bigint: bigint/sources/bigint.c bigint/sources/errors.c
	gcc -c bigint/sources/bigint.c -o $(OBJECTS_DIR)/bigint.o
	gcc -c bigint/sources/errors.c -o $(OBJECTS_DIR)/errors.o	