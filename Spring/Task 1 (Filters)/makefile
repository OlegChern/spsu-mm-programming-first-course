.PHONY: all clean

SOURCES_DIR = sources
OBJECTS_DIR = objects
EXE_NAME = filter

all: objects_dir main filters bmp bgr_map
	g++ -std=c++11 $(OBJECTS_DIR)/*.o -o $(EXE_NAME) -lm

clean:
	rm -rf $(EXE_NAME) $(OBJECTS_DIR)

objects_dir:
	mkdir -p $(OBJECTS_DIR)
		
main: $(SOURCES_DIR)/main.cpp
	g++ -std=c++11 -c $(SOURCES_DIR)/$@.cpp -o $(OBJECTS_DIR)/$@.o

filters: $(SOURCES_DIR)/filters.cpp
	g++ -std=c++11 -c $(SOURCES_DIR)/$@.cpp -o $(OBJECTS_DIR)/$@.o

bmp: $(SOURCES_DIR)/bmp.cpp
	g++ -std=c++11 -c $(SOURCES_DIR)/$@.cpp -o $(OBJECTS_DIR)/$@.o

bgr_map: $(SOURCES_DIR)/bgr_map.cpp
	g++ -std=c++11 -c $(SOURCES_DIR)/$@.cpp -o $(OBJECTS_DIR)/$@.o