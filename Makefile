CC = g++
CFLAGS = -std=c++17
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = Game
SRC_FILES = Levels.cpp Menu.cpp bossFight.cpp SpaceMap.cpp GameState.cpp Graph.cpp main.cpp 
HEADER_FILES = Levels.h Menu.h bossFight.h SpaceMap.h GameState.h Graph.h

all: $(TARGET)

$(TARGET): $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET) $(SFML_LIBS)

clean:
	rm -f $(TARGET)
