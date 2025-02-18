# Define variables for reuse
ENGINE_SRC := engine/src/*.cpp
ENGINE_INCLUDE := -Iengine/include
ENGINE_BUILD_DIR := engine/build
ENGINE_LIB := $(ENGINE_BUILD_DIR)/libengine.a

GAME_SRC := game/main.cpp
GAME_INCLUDE := -Igame/include -Iengine/include
GAME_BUILD_DIR := game/build
GAME_OUTPUT_WIN := $(GAME_BUILD_DIR)/main.exe
GAME_OUTPUT_MAC := $(GAME_BUILD_DIR)/main

# Default target
all: engine game

# Build the engine library
engine:
ifeq ($(PLATFORM),WIN)
	@echo "Building engine for Windows..."
	g++ -std=c++17 $(ENGINE_INCLUDE) -c $(ENGINE_SRC) && \
	llvm-ar rcs $(ENGINE_LIB) *.obj && \
	del *.obj
else ifeq ($(PLATFORM),MAC)
	@echo "Building engine for macOS..."
	clang++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa \
	-framework GLUT -framework OpenGL $(ENGINE_INCLUDE) -c $(ENGINE_SRC) && \
	ar rcs $(ENGINE_LIB) *.o && \
	rm -f *.o
else
	@echo "Error: Please specify PLATFORM=WIN or PLATFORM=MAC"
	@exit 1
endif

# Build the game executable
game: engine
ifeq ($(PLATFORM),WIN)
	@echo "Building game for Windows..."
	g++ -std=c++17 $(GAME_SRC) -Lengine/lib -L$(ENGINE_BUILD_DIR) $(GAME_INCLUDE) \
	-lraylib -lengine -lgdi32 -lwinmm -o $(GAME_OUTPUT_WIN)
else ifeq ($(PLATFORM),MAC)
	@echo "Building game for macOS..."
	clang++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa \
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
	rm -rf $(ENGINE_BUILD_DIR)/*.a *.o *.obj $(GAME_OUTPUT_WIN) $(GAME_OUTPUT_MAC)

# Phony targets to avoid conflicts with file names
.PHONY: all engine game clean
