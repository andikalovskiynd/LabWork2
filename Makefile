CXXFLAGS = -std=c++17 -Wall -Werror -Wpedantic -g

LDFLAGS =

CXX = g++

SRC_DIR = src
OBJ_DIR = build
INCLUDE_DIR = include

SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.cpp')

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $< 

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
