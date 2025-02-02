sources = $(wildcard src/*.cpp)
frameworks = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
flags = $(frameworks) -std=c++23 -Iinclude -Llib -Wall -Wextra -lraylib

main:
	clang++ $(flags) $(sources)

clean:
	rm -f a.out
