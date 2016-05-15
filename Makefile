# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11 -Wall

# File names
OUTPUT = hz
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTPUT)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(OUTPUT) $(OBJECTS)
