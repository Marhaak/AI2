CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Main.cpp Agent.cpp Environment.cpp Graphix.cpp Node.cpp PathFinding.cpp SeachCell.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hello

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lSDL

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@