COMPILER = clang
OPTIONS = -g -pedantic -Wall -Wextra -Wshadow -Wunreachable-code
COMPILE = $(COMPILER) $(OPTIONS)
BUILD = build
SRCDIR = src

# Define source file extensions
SRC_EXT = c

# Find all source files in SRCDIR and its subdirectories
SRC_FILES = $(shell find $(SRCDIR) -type f -name *.$(SRC_EXT))

# Generate object file paths from source file paths
OBJ_FILES = $(patsubst $(SRCDIR)/%.$(SRC_EXT),$(BUILD)/%.$(SRC_EXT).o,$(SRC_FILES))

# Define the final target
TARGET = a.out

# Create a list of unique subdirectories in SRCDIR
SUBDIRS := $(sort $(dir $(SRC_FILES)))

# Create subdirectories in BUILD directory
BUILD_SUBDIRS := $(patsubst $(SRCDIR)/%, $(BUILD)/%, $(SUBDIRS))

# Define phony targets
.PHONY: all clean

# Default target
all: $(BUILD) $(BUILD_SUBDIRS) $(TARGET)

# Build the executable
$(TARGET): $(OBJ_FILES)
	$(COMPILE) $^ -o $@

# Build object files from source files
$(BUILD)/%.$(SRC_EXT).o: $(SRCDIR)/%.$(SRC_EXT) | $(BUILD) $(BUILD_SUBDIRS)
	$(COMPILE) -c $< -o $@

# Create BUILD and BUILD_SUBDIRS directories
$(BUILD) $(BUILD_SUBDIRS):
	mkdir -p $@

clean:
	rm -rf $(BUILD) $(TARGET)