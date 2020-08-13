CC=g++
C=gcc
CFLAGS=-Wall -g
BINS=Application

# Additional include directories.
GLFW_HEADER_PATH=dependencies/GLFW/include
GLAD_HEADER_PATH=dependencies/GLAD/include

# Additional library directories.
GLFW_LIBRARY_PATH=dependencies/GLFW/lib
GLAD_SRC_PATH=dependencies/GLAD/src

# Virtual paths.
vpath %.cpp src
vpath %.c dependencies/GLAD/src
vpath %.h dependencies/GLAD/include

all: ${BINS}

Application.o: Application.cpp
	${CC} ${CFLAGS} -I${GLFW_HEADER_PATH} -I${GLAD_HEADER_PATH} -c $<

glad.o: glad.c
	${C} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

Application: Application.o glad.o
	${CC} ${CFLAGS} -o $@ $^ -L${GLFW_LIBRARY_PATH} -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

clean:
	rm *.o ${BINS}