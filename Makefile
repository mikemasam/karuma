CXX = g++

# path #
SRC_PATH = ./src
BUILD_PATH = ./build

# executable # 
BIN_NAME = bin 

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)
#SOURCES += main.cpp

# flags #
COMPILE_FLAGS = -std=c++14 -Wall -Wextra -g
INCLUDES = -I ./include 
# Space-separated pkg-config libraries used by this project
LIBS = -lboost_filesystem -lboost_thread -lboost_system -lpthread -lcrypto


.PHONY: default_target
default_target: release

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: init 
	$(MAKE) all

.PHONY: dirs
init:
	@echo "Building app..."
	mkdir -p $(dir $(OBJECTS))

.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	$(RM) $(BIN_NAME)
	echo "Deleting directory"
	$(RM) -R $(BUILD_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BUILD_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	$(RM) $(BIN_NAME)
	ln -s $(BUILD_PATH)/$(BIN_NAME) $(BIN_NAME)

# Creation of the executable
$(BUILD_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) -o $@ $(LIBS)

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@ $(LIBS)
