# Define the compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g
LDFLAGS = `pkg-config --libs raylib`

# Define the source and build directories
SRCDIR = src
INCLUDEDIR = include
BUILDDIR = build

# Define the source and object files
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Define the executable name
EXE = tower

# Define the default rule
all: $(EXE)

# Define the rule to link the executable
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Define the rule to compile the object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c -o $@ $<

# Define the rule to clean the build directory
clean:
	rm -rf $(BUILDDIR)/*.o $(EXE)
