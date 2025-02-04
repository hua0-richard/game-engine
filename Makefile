# default:
# 	clang++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -Llib -Iinclude -lraylib main.cpp -o main

default: 
	g++ -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -Llib -Iinclude -lraylib main.cpp -o main
