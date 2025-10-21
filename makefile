GXX = g++
FLAGS = -O2
LIBS = -I./src/include/ -lblas -lopenblas -lcublas -lcudart
lib_name = linALG.a

srcs := $(shell find ./src -name "*.cc")
objs := $(shell find . -name ".o")

all:
	${GXX} ${FLAGS} -c ${srcs} ${LIBS}
lib:
	ar rvs linALG.a matrix.o ./src/extern/cublas.o flatten.o
main:
	${GXX} main.cc ${lib_name} ${LIBS} -o ou