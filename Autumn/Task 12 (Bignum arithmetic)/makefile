.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = bignum

all: objects_dir main bigint errors
	gcc $(OBJECTS_DIR)/*.o -o $(EXE_NAME)

clean:
	rm -rf $(EXE_NAME) $(OBJECTS_DIR)

objects_dir:
	mkdir -p $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

bigint: $(SOURCES_DIR)/bigint.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

errors: $(SOURCES_DIR)/errors.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o
