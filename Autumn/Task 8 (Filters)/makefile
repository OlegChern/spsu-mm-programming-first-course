.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = filter

all: objects_dir main filters bmp bgr_map
	gcc $(OBJECTS_DIR)/*.o -o $(EXE_NAME) -lm

clean:
	if exist $(EXE_NAME).exe del /Q $(EXE_NAME).exe
	if exist $(OBJECTS_DIR) rmdir /S /Q $(OBJECTS_DIR)

objects_dir:
	if not exist $(OBJECTS_DIR) mkdir $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

filters: $(SOURCES_DIR)/filters.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

bmp: $(SOURCES_DIR)/bmp.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o

bgr_map: $(SOURCES_DIR)/bgr_map.c
	gcc -c $(SOURCES_DIR)/$@.c -o $(OBJECTS_DIR)/$@.o