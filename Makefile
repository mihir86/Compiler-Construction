CXX = g++
INCLUDE_DIR = ./include
SRC_DIR = ./src
BUILD_DIR = ./build
CXXFLAGS = -Wall -Wextra -Wshadow -O3 -MMD -I$(INCLUDE_DIR)
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

$(info Source files: $(SRC_FILES))
$(info Object files: $(OBJ_FILES))
main: $(OBJ_FILES)
	$(CXX) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	$(info $@)

-include $(OBJ_FILES:.o=.d)

.PHONY : clean
clean:
	rm $(BUILD_DIR)/*.exe $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d