
# Compiler settings
CXX      := g++
DEPFLAGS := -MMD -MP
CXXFLAGS := -Wall -Wextra -Iinclude/ $(DEPFLAGS)
LDFLAGS  := 
TARGET   := bin/advanced_calculator.exe
SRC_DIR  := src
OBJ_DIR  := obj

# Debug vs Release
BUILD := debug
ifeq ($(BUILD), debug)
	CXXFLAGS += -O0 -g
else ifeq ($(BUILD), release)
	CXXFLAGS += -O3 -DNDEBUG
endif

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Default target
all: $(TARGET)


# Link object files
$(TARGET): $(OBJS)
	@if not exist $(@D) mkdir $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@


# Compile each .cpp file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(@D) mkdir $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Clean build
clean:
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	if exist $(TARGET) del $(TARGET)


# Run the program
run: $(TARGET)
	$(TARGET)

# Include auto-generated dependencies
-include $(DEPS)

.PHONY: all clean run