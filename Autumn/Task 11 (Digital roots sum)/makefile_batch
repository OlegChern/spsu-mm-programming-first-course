.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = digital_roots

all: objects_dir main
	gcc $(OBJECTS_DIR)/*.o -o $(EXE_NAME) -lm -Wl,--stack,16776256

clean:
	if exist $(EXE_NAME).exe del /Q $(EXE_NAME).exe
	if exist $(OBJECTS_DIR) rmdir /S /Q $(OBJECTS_DIR)

objects_dir:
	if not exist $(OBJECTS_DIR) mkdir $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o