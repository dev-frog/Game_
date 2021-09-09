# Compiler
CC :=g++
# compiler flag
PKGS :=sdl2
CFLAGS :=`sdl2-config --libs --cflags` -ggdb3 -O0 --std=c++14 -Wall -lSDL2_image -lm
LIBS :=`pkg-config -libs sdl2`

# Execution
EXEC := game

# source files here
SRCS := src/*.cpp


gp: $(SRCS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS) $(LIBS)