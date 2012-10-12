all: gl

gl: sample.c
	gcc -g sample.c -o gl -lGL -lGLU -lglut

clean:
	rm -rf *o gl


