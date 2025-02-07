.PHONY: default clean

default:
ifeq ($(PLATFORM),WIN)
	@echo "Building for Windows..."
	g++ -std=c++17 main.cpp -Llib -Iinclude -lraylib -lgdi32 -lwinmm -o main
else ifeq ($(PLATFORM),MAC)
	@echo "Building for macOS..."
	clang++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa \
	-framework GLUT -framework OpenGL -Llib -Iinclude -lraylib main.cpp -o main
else
	@echo "Error: Please specify PLATFORM=WIN or PLATFORM=MAC"
	@exit 1
endif