# Executable names:
EXE = final_project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o graph.o Vertex.o GraphInitializer.o BFS.o AlgoImpl.o UserInterface.o

# Generated files
CLEAN_RM = images/Out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk
