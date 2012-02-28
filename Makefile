# Compilador usado

CXX = g++

# Listado de directorios

SRC = source
OBJ = object
HEAD = header
BIN = bin

# Variables

objects = $(OBJ)/Tree.o $(OBJ)/TreeNode.o $(OBJ)/TestTree.o

# Compilation options

FLAGS = -Wall -g -c -I$(HEAD)

# Targets

all : $(BIN)/TestTree

# Compilation instructions

$(OBJ)/TreeNode.o : $(SRC)/TreeNode.cpp $(HEAD)/TreeNode.h
	@echo "Building TreeNode ..."
	@$(CXX) $(FLAGS) $(SRC)/TreeNode.cpp -o $(OBJ)/TreeNode.o

$(OBJ)/Tree.o : $(SRC)/Tree.cpp $(HEAD)/Tree.h $(HEAD)/TreeNode.h
	@echo "Building Tree ..."
	@$(CXX) $(FLAGS) $(SRC)/Tree.cpp -o $(OBJ)/Tree.o

$(OBJ)/TestTree.o : $(SRC)/TestTree.cpp $(HEAD)/Tree.h
	@echo "Building TestTree ..."
	@$(CXX) $(FLAGS) $(SRC)/TestTree.cpp -o $(OBJ)/TestTree.o

# Binaries generation

$(BIN)/TestTree : $(objects)
	@echo "Generating 'TestTree' binaries ..."
	@$(CXX) $(objects) -o $(BIN)/TestTree

# Clean up macro

.PHONY : clean
clean:
	@echo "Cleaning up ..."
	@-rm -f $(OBJ)/* $(BIN)/* $(HEAD)/*~ $(SRC)/*~ *~
