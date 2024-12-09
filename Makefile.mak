# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source and header files
SOURCES = PA04_Main_Assert.c CourseUtilities.c BasicUtilities.c File_Input_Utility.c RoomUtilities.c Console_IO_Utility.c
HEADERS = StandardConstants.h

# Object files (one for each source file)
OBJECTS = $(SOURCES:.c=.o)

# Target executable
TARGET = PA04_Main_Assert

# Default rule to build the program
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Rule for compiling source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)