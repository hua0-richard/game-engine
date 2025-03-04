# Define variables for reuse
ENGINE_SRC := engine/src/*.cpp
ENGINE_INCLUDE := -Iengine/include
ENGINE_BUILD_DIR := engine/build
ENGINE_LIB := $(ENGINE_BUILD_DIR)/libengine.a
ENGINE_OBJ_DIR := $(ENGINE_BUILD_DIR)/obj
ENGINE_OBJS := $(patsubst engine/src/%.cpp,$(ENGINE_OBJ_DIR)/%.o,$(wildcard engine/src/*.cpp))

GAME_SRC := game/main.cpp
GAME_INCLUDE := -Igame/include -Iengine/include
GAME_BUILD_DIR := game/build
GAME_OUTPUT_WIN := $(GAME_BUILD_DIR)/main
GAME_OUTPUT_MAC := $(GAME_BUILD_DIR)/main

# Default target
all: engine game

# Create directories
$(ENGINE_OBJ_DIR):
	mkdir -p $(ENGINE_OBJ_DIR)

# Compile individual source files
$(ENGINE_OBJ_DIR)/%.o: engine/src/%.cpp | $(ENGINE_OBJ_DIR)
ifeq ($(PLATFORM),WIN)
	@echo "Compiling $<..."
	g++ -std=c++17 $(ENGINE_INCLUDE) -c $< -o $@
else ifeq ($(PLATFORM),MAC)
	@echo "Compiling $<..."
	g++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa \
	-framework GLUT -framework OpenGL $(ENGINE_INCLUDE) -c $< -o $@
endif

# Build the engine library
engine: $(ENGINE_OBJS)
ifeq ($(PLATFORM),WIN)
	@echo "Building engine library for Windows..."
	ar rcs $(ENGINE_LIB) $(ENGINE_OBJS)
else ifeq ($(PLATFORM),MAC)
	@echo "Building engine library for macOS..."
	ar rcs $(ENGINE_LIB) $(ENGINE_OBJS)
else
	@echo "Error: Please specify PLATFORM=WIN or PLATFORM=MAC"
	@exit 1
endif

# Build the game executable
game: engine
ifeq ($(PLATFORM),WIN)
	@echo "Building game for Windows..."
	g++ -std=c++17 $(GAME_SRC) -Lengine/lib -L$(ENGINE_BUILD_DIR) $(GAME_INCLUDE) \
    -lengine -lraylib -lopengl32 -lgdi32 -lwinmm -o $(GAME_OUTPUT_WIN)
else ifeq ($(PLATFORM),MAC)
	@echo "Building game for macOS..."
	g++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa \
	-framework GLUT -framework OpenGL $(GAME_SRC) \
	 engine/lib/libraylib.a -L$(ENGINE_BUILD_DIR) -lengine \
	$(GAME_INCLUDE) \
	-o $(GAME_OUTPUT_MAC)
else
	@echo "Error: Please specify PLATFORM=WIN or PLATFORM=MAC"
	@exit 1
endif

# Clean build artifacts
clean:
	@echo "Cleaning up build artifacts..."
	rm -rf $(ENGINE_BUILD_DIR)/*.a $(ENGINE_OBJ_DIR)/*.o *.o *.obj $(GAME_OUTPUT_WIN) $(GAME_OUTPUT_MAC)
	mkdir -p $(ENGINE_BUILD_DIR) $(ENGINE_OBJ_DIR) $(GAME_BUILD_DIR)

# Phony targets to avoid conflicts with file names
.PHONY: all engine game clean
