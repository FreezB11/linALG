# GXX = g++
# FLAGS = -O2
# LIBS = -I./src/include/ -lblas -lopenblas -lcublas -lcudart
# lib_name = linALG.a

# srcs := $(shell find ./src -name "*.cc")
# objs := $(shell find . -name ".o")

# all:
# 	${GXX} ${FLAGS} -c ${srcs} ${LIBS}
# lib:
# 	ar rvs linALG.a matrix.o ./src/extern/cublas.o flatten.o
# main:
# 	${GXX} main.cc ${lib_name} ${LIBS} -o ou

# Compiler and flags
GXX = g++
NVCC = nvcc
CXXFLAGS = -O2 -std=c++17
INCLUDE = -I./src/include
LIBS = -lblas -lopenblas -lcublas -lcudart

# Directories
SRCDIR = ./src
EXTERNDIR = ./src/extern
OBJDIR = ./obj
BINDIR = ./bin

# Source files
SRCS = $(shell find $(SRCDIR) -name "*.cc")
OBJS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SRCS))
EXTERN_OBJS = $(OBJDIR)/cublas.o

# Output
LIB_NAME = liblinALG.a
MAIN_EXE = $(BINDIR)/ou

# Ensure directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Default target
all: $(LIB_NAME) $(MAIN_EXE)

# Compile object files from .cc
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(dir $@)
	$(GXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Compile cublas.cu from extern
$(OBJDIR)/cublas.o: $(EXTERNDIR)/cublas.cu
	$(NVCC) -c $< -o $@

# Build static library
$(LIB_NAME): $(OBJS) $(EXTERN_OBJS)
	ar rvs $@ $^

# Build main executable
$(MAIN_EXE): main.cc $(LIB_NAME)
	$(GXX) main.cc $(LIB_NAME) $(INCLUDE) $(LIBS) -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(LIB_NAME) $(BINDIR)

.PHONY: all clean
