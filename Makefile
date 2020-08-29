CC=clang++
C=clang
CFLAGS=-Wall -g
BINS=Application

# Additional include directories.
GLFW_HEADER_PATH=dependencies/GLFW/include
GLAD_HEADER_PATH=dependencies/GLAD/include
STB_IMAGE_HEADER_PATH=dependencies/stbImage

# Additional library directories.
GLFW_LIBRARY_PATH=dependencies/GLFW/lib
GLAD_SRC_PATH=dependencies/GLAD/src

# Virtual paths.
vpath %.cpp src
vpath %.c dependencies/GLAD/src dependencies/stbImage
vpath %.h dependencies/GLAD/include/glad src

all: ${BINS}

stb_image.o: stb_image.c
	${C} ${CFLAGS} -I${STB_IMAGE_HEADER_PATH} -c $<

Application.o: Application.cpp
	${CC} ${CFLAGS} -I${GLFW_HEADER_PATH} -I${GLAD_HEADER_PATH} -I${STB_IMAGE_HEADER_PATH} -c $<

Shader.o: Shader.cpp Shader.h
	${CC} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

glad.o: glad.c
	${C} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

VertexBufferLayout.o: VertexBufferLayout.cpp VertexBufferLayout.h
	${CC} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

VertexArray.o: VertexArray.cpp VertexArray.h
	${CC} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

Application: Application.o glad.o Shader.o VertexBuffer.o\
			 VertexBufferLayout.o VertexArray.o IndexBuffer.o Renderer.o stb_image.o
	${CC} ${CFLAGS} -o $@ $^ -L${GLFW_LIBRARY_PATH} -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

VertexBuffer.o: VertexBuffer.cpp VertexBuffer.h
	${CC} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

IndexBuffer.o: IndexBuffer.cpp IndexBuffer.h
	${CC} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

Renderer.o: Renderer.cpp Renderer.h
	${CC} ${CFLAGS} -I${GLAD_HEADER_PATH} -c $<

clean:
	rm *.o ${BINS}