.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = confract

all: main fractions
	gcc -o $(EXE_NAME) $(OBJECTS_DIR)/*.o -lm

clean:
	rm -rf $(EXE_NAME) $(OBJECTS_DIR)

objects_dir:
	mkdir -p $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

fractions: $(SOURCES_DIR)/fractions.c objects_dir
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o