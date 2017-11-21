.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = converter

all: main str_funcs bit_funcs
	gcc $(OBJECTS_DIR)/*.o -o $(EXE_NAME) -lm

clean:
	rm -rf $(EXE_NAME).exe $(OBJECTS_DIR)

objects_dir:
	mkdir -p $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

str_funcs: $(SOURCES_DIR)/str_funcs.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

bit_funcs: $(SOURCES_DIR)/bit_funcs.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o