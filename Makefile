# I'm using the g++ and not the llvm c compiler... I'm sorry
CC_FLAGS = -Wall -Iinclude -std=c++11 -fPIC
LINK_FLAGS = -shared
# Environment
SHELL=/bin/sh
MKDIR=mkdir
CP=cp
GREP=grep
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Directorys
BUILDDIR = build/
SOURCEDIR = src/

# File names
EXEC = $(BUILDDIR)libALGP.so
SOURCES = $(wildcard $(SOURCEDIR)*.cpp)
OBJECTS_TMP = $(SOURCES:.cpp=.o)
OBJECTS = $(OBJECTS_TMP:$(SOURCEDIR)%=$(BUILDDIR)%)

$(BUILDDIR)%.o: $(SOURCEDIR)%.cpp
	$(CCC) -c $< $(CC_FLAGS) -o $@


# Main target
$(EXEC): $(OBJECTS)
	$(CCC) $(OBJECTS) $(LINK_FLAGS) -o $(EXEC)



# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

