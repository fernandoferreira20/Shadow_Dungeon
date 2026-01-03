# --- Project Configuration ---
TARGET = shadow_dungeon
CC = gcc

LIBS = -lm

# Important flags:
# -Include: Says to look for headers (.h) in the include folder
# -Isrc: Says to look for headers inside of src
# -Iassests: Says to look for headers inside of assests
CFLAGS = -Wall -Wextra -g -O2 -Iinclude -Isrc -Iassets

# We look for .c files only in the 'src' and 'assets' folders
SRCS := $(shell find src assets -name '*.c')

# Creates the list of objects (.o) while maintaining the folder structure
OBJS := $(SRCS:.c=.o)

# --- Rules ---

all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "Linking the game..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	@echo "Build complete! Run with: ./$(TARGET)"

# Generic rule to compile in any .c in .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning compiled files..."
	rm -f $(OBJS) $(TARGET)

run: all 
	./$(TARGET)

#Use 'make debug' to see what files it will try to compile
debug:
	@echo "Source files detected:"
	@echo $(SRCS)