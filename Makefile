# ===================
# Compiler being used
# ===================

CXX = g++

# ==============
# Directory list
# ==============

# SOURCE
SRC = src
# OBJECT
OBJ = obj
# INCLUDE
INC = inc
# BINARY
BIN = bin
# DOCUMENT
DOC = doc

# =========
# Variables
# =========

objects = $(OBJ)/Tree.o $(OBJ)/TreeNode.o $(OBJ)/TestTree.o $(OBJ)/TreeGenericException.o $(OBJ)/RootNotErasableException.o

# ===================
# Compilation options
# ===================

FLAGS = -Wall -g -c -I$(INC)

# =======
# Targets
# =======

all : $(BIN)/TestTree

# ========================
# Compilation instructions
# ========================

$(OBJ)/TreeGenericException.o : $(SRC)/TreeGenericException.cpp $(INC)/TreeGenericException.h
	@echo "Building TreeGenericException ..."
	@$(CXX) $(FLAGS) $(SRC)/TreeGenericException.cpp -o $(OBJ)/TreeGenericException.o

$(OBJ)/RootNotErasableException.o : $(SRC)/RootNotErasableException.cpp $(INC)/TreeGenericException.h $(INC)/RootNotErasableException.h
	@echo "Building RootNotErasableException ..."
	@$(CXX) $(FLAGS) $(SRC)/RootNotErasableException.cpp -o $(OBJ)/RootNotErasableException.o

$(OBJ)/TreeNode.o : $(SRC)/TreeNode.cpp $(INC)/TreeNode.h
	@echo "Building TreeNode ..."
	@$(CXX) $(FLAGS) $(SRC)/TreeNode.cpp -o $(OBJ)/TreeNode.o

$(OBJ)/Tree.o : $(SRC)/Tree.cpp $(INC)/Tree.h $(INC)/TreeNode.h
	@echo "Building Tree ..."
	@$(CXX) $(FLAGS) $(SRC)/Tree.cpp -o $(OBJ)/Tree.o

$(OBJ)/TestTree.o : $(SRC)/TestTree.cpp $(INC)/Tree.h $(INC)/RootNotErasableException.h
	@echo "Building TestTree ..."
	@$(CXX) $(FLAGS) $(SRC)/TestTree.cpp -o $(OBJ)/TestTree.o

# ===================
# Binaries generation
# ===================

$(BIN)/TestTree : $(objects)
	@echo "Generating 'TestTree' binaries ..."
	@$(CXX) $(objects) -o $(BIN)/TestTree

# ==============
# Clean up macro
# ==============

.PHONY : clean
clean:
	@echo "Cleaning up ..."
	@-rm -f $(OBJ)/* $(BIN)/* $(INC)/*~ $(SRC)/*~ *~
