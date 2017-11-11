.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = hash_map

all: objects_dir main str_funcs list pair array_utils hash_map
	gcc $(OBJECTS_DIR)/*.o -o $(EXE_NAME) -lm

clean:
	if exist $(EXE_NAME).exe del /Q $(EXE_NAME).exe
	if exist $(OBJECTS_DIR) rmdir /S /Q $(OBJECTS_DIR)

objects_dir:
	if not exist $(OBJECTS_DIR) mkdir $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

str_funcs: $(SOURCES_DIR)/str_funcs.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

list: $(SOURCES_DIR)/list.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

pair: $(SOURCES_DIR)/pair.c 
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

array_utils: $(SOURCES_DIR)/array_utils.c 
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

hash_map: $(SOURCES_DIR)/hash_map.c 
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

