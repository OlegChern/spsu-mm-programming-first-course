.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = fraction

all: main str_funcs fractions
	gcc $(OBJECTS_DIR)/*.o -o $(EXE_NAME) -lm

clean:
	if exist $(EXE_NAME).exe del /Q $(EXE_NAME).exe
	if exist $(OBJECTS_DIR) rmdir /S /Q $(OBJECTS_DIR)

objects_dir:
	if not exist $(OBJECTS_DIR) mkdir $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

str_funcs: $(SOURCES_DIR)/str_funcs.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

fractions: $(SOURCES_DIR)/fractions.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o