CC = clang++
CFLAGS = -Wall -std=c++17 -g
INCLUDE = include

SRC = $(wildcard src/*.cpp)
OBJ = $(addprefix build/,$(notdir $(SRC:.cpp=.o)))

EXE = tower

LIBPATH = lib
LIBS = -lraylib

# default
TARGET = linux

ifeq ($(TARGET),linux)
    RM = rm -f
	LIBPATH := 'pkg-config --libs raylib'
else ifeq ($(TARGET),win)
	RM = del /Q
	LIBPATH := $(LIBPATH)/win_amd64
	LIBS := -lraylib -lopengl32 -lgdi32 -lwinmm
endif

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -L$(LIBPATH) $^ -o $@ $(LIBS)

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXE)
