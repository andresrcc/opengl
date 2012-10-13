all: viewer

viewer: viewer.c
	gcc -g viewer.c -o viewer -lGL -lGLU -lglut

clean:
	rm -rf *o gl


