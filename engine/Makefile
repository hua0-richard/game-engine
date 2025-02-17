.PHONY: default

default:
ifeq ($(PLATFORM),WIN)
	@echo "Building for Windows..."
	g++ -std=c++17 main.cpp src/*.cpp -Llib -Iinclude -lraylib -lgdi32 -lwinmm -o build/main
else ifeq ($(PLATFORM),MAC)
	@echo "Building for macOS..."
	clang++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa \
	-framework GLUT -framework OpenGL -Llib -Iinclude -lraylib main.cpp src/*.cpp -o build/main
else
	@echo "Error: Please specify PLATFORM=WIN or PLATFORM=MAC"
	@exit 1
endifat