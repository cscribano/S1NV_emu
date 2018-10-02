OBJS = $(wildcard *.cpp) $(wildcard */*.cpp)

CC = g++

COMPILER_FLAGS = -w -I/usr/include/SDL2 -L/usr/lib/x86_64-linux-gnu

LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_mixer

OBJ_NAME = S1NV

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
