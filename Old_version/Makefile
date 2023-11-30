CC = g++
CFLAGS = -std=c++17
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = prog
SRC_FILES = VerriPG.cpp main.cpp
HEADER_FILES = VerriPG.h

all: $(TARGET)

$(TARGET): $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET) $(SFML_LIBS)

clean:
	rm -f $(TARGET)
