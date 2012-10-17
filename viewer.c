#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "glm.h"
#include <string.h>
#include <stdint.h>

/**
 * Variables Globales
 */

//Coordeadas de la Camara
float azimut = 0.78; 
float elevacion = 0.78;
float distancia = 50.0;

//Objetos

//Objeto seleccionado actualmente
int seleccion = 1;

//--Para importar .obj
GLMmodel *modelo = NULL;

//--Para moverlo--


struct objeto{
//Coordenadas
  float x;
  float y;
  float z;

};typedef struct objeto figura;


//Arreglo de objetos y sus coordenadas
figura objetos[4];

/**
 * Sistema de Referencia
 */

void sistema_referencia(){
  int i;

  //Inicio del sistema de referencia
  glPushMatrix();

  glColor3f(.3, .3, .3);
  //Malla del plano x-z 

   //Rectangulo
  glBegin(GL_QUADS); 
  glVertex3f( -10, -0.001, -10);
  glVertex3f( 10, -0.001, -10);  
  glVertex3f( 10, -0.001, 10);
  glVertex3f( -10, -0.001, 10);
  glEnd();

   //Lineas de la malla
  glBegin(GL_LINES);
  for (i=-10; i<=10; i++){

    glColor3f(.25,.25,.25);
    glVertex3f(i,0,-10);
    glVertex3f(i,0,10);
    
    glColor3f(.25, .25, .25);
    glVertex3f(-10,0,i);
    glVertex3f(10,0,i);

  };
  glEnd();

  //Maya del plano x-y
  glColor3f(.5, .2, .4);
  glBegin(GL_QUADS); 
  glVertex3f( -10.0, -10.0, 0.0);
  glVertex3f( 10.0, -10-0, 0.0);
  glVertex3f( 10.0, 10.0, 0.0);
  glVertex3f( -10.0, 10, 0.0);
  glEnd();

  glBegin(GL_LINES);
  for (i=-10; i<=10; i++){
 
    glColor3f(.25,.25,.25);
    glVertex3f(i,-10,0);
    glVertex3f(i,10,0);    
    glVertex3f(-10.0,i,0);
    glVertex3f(10,i,0);

  };

  glEnd();


  //Maya del plano z-y
  glColor3f(.3, .3, .2);
  glBegin(GL_QUADS); 
  glVertex3f( 0.0, -10.0, 10.0);
  glVertex3f( 0.0, -10.0, -10.0);
  glVertex3f( 0.0, 10.0, -10.0);
  glVertex3f( 0.0, 10.0, 10.0);
  glEnd();

  glBegin(GL_LINES);
  for (i=-10; i<=10; i++){

    glColor3f(.25,.25,.25);
    glVertex3f(0.0,-10.0,i);
    glVertex3f(0.0,10.0,i);
    glVertex3f(0.0,i,-10);
    glVertex3f(0.0,i,10);

  };

  glEnd();

  //Final
  glPopMatrix();
}



/**
 * Agrega objetos ya creados
 * al modelo
 */

void agregar_objeto(char *path_archivo, int q){

  //Dibujamos
  glPushMatrix();
  glTranslatef(objetos[q].x,objetos[q].y,objetos[q].z);
  glColor3f(2,8,3);

  modelo = glmReadOBJ(path_archivo);
  if (!modelo) exit (0); //si no existe, exit

  glmUnitize(modelo);
  glmFacetNormals(modelo);
  glmVertexNormals(modelo, 90.0);

  glmDraw(modelo, GLM_SMOOTH | GLM_MATERIAL);
  
  glPopMatrix();
}

void dibujar_cubo(GLfloat a, GLfloat b, GLfloat c, GLfloat anch, GLfloat alt, GLfloat prof){
	/*unsigned char * textura;
	GLuint idTextura;
	FILE *file;
	file = fopen("cajax.bmp","rb");
	textura = (unsigned char*) malloc(256*256*4);
	fread(textura, 256*256*4, 1, file);
	fclose(file);
	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);
	glTexImage2D(GL_TEXTURE_2D,0,3,256,256,0,GL_RGB,GL_UNSIGNED_BYTE,textura);
	free(textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	*/
	anch = anch/2;
	alt = alt/2;
	prof = prof/2;
	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glNormal3f(0.0f,1.0f,0.0f);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(-anch,prof,alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(-anch,prof,-alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(anch,prof,-alt);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(anch,prof,alt);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(1.0f,0.0f,0.0f);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(anch,prof,-alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(anch,prof,alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(anch,-prof,alt);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(anch,-prof,-alt);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(0.0f,-1.0f,0.0f);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(anch,-prof,alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(-anch,-prof,alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(-anch,-prof,-alt);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(anch,-prof,-alt);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(-1.0f,0.0f,0.0f);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(-anch,-prof,-alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(-anch,prof,-alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(-anch,prof,alt);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(-anch,-prof,alt);
	glEnd(); 
	glBegin(GL_QUADS);
		glNormal3f(0.0f,0.0f,1.0f);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(-anch,prof,alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(-anch,-prof,alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(anch,-prof,alt);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(anch,prof,alt);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(0.0f,0.0f,-1.0f);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(-anch,prof,-alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(-anch,-prof,-alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(anch,-prof,-alt);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(anch,prof,-alt);
	glEnd();

	//glDisable(GL_TEXTURE_2D);
}


void dibujar_Joe(){
  //Cabeza
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
 	 glTranslatef(0,0.75,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.5,0.5,0.5);
  glPopMatrix();
  //torso
  glColor3f(1.0,0,1.0);		
  glPushMatrix();	
 	 glTranslatef(0,0,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.3,0.15,1);
  glPopMatrix();
  //BrazoI
  glColor3f(1.0,1.0,0);		
  glPushMatrix();	
 	 glTranslatef(0.35,0.2,-0.15);
  	 glRotatef(45.0,0,1.0,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.45,0.1,0.1);
  glPopMatrix();
  //BrazoD
  glColor3f(1.0,1.0,0);		
  glPushMatrix();	
 	 glTranslatef(-0.35,0.2,-0.15);
	 glRotatef(-45.0,0,1.0,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.45,0.1,0.1);
  glPopMatrix();
  //PiernaI
 glColor3f(0,1.0,1.0);		
  glPushMatrix();	
 	 glTranslatef(0.15,-0.5,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.1,0.1,0.5);
  glPopMatrix();
  //PiernaD
 glColor3f(0,1.0,1.0);		
  glPushMatrix();	
 	 glTranslatef(-0.15,-0.5,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.1,0.1,0.5);
  glPopMatrix();



}


/**
 *Dibuja la escena
 */ 
void display(){

  //Reseteamos la matriz de transformacion de modelo
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Coloreamos la ventana
  glClearColor(0.0, 0.0, 0.0, 0.0);
  
  //IMPORTANTE:limpeamos el buffer de color y 
  //de profundidad.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Controles de la Camara

  gluLookAt(distancia * sin(elevacion) * sin(azimut),
	    distancia * cos(elevacion),
	    distancia * sin(elevacion) * cos(azimut),
	    0.0,0.0,0.0,
	    0.0,1.0,0.0);

  //Establecemos el sist. de referencia
  //sistema_referencia();

  //Agregamos objetos al modelo
  agregar_objeto("objetos/porsche.obj",1);
//Jorge
  dibujar_Joe();
    //
  glutSwapBuffers();
}


/**
 * Acciones a llevar a cabo si se cambia el
 * tamaño de la ventana
 */
void cambios_ventana(int w, int h){

  float aspectratio;
  if (h == 0)
    h=1;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  aspectratio = (float) w / (float) h;

  gluPerspective(35.0, aspectratio, 1.0, 300.0);

}

/**
 * Recibe la entrada del teclado, y 
 * efectua los cambios a la camara
 */

void teclado (unsigned char tecla, int x, int y){

  /* Una fraccion del vector de
   * direccion de la camara 
   * (linea de observacion)
   */
  float k = 0.1;

  switch(tecla){
     case 27:
       exit(0);
     case 'w':
	//subir: - distancia, + elevacion
       elevacion -= k;
       break;
     case 'a':
       //izquierda: 
       azimut -= k;
       break;
     case 's':
	//abajo:
       elevacion += k;
       break;
     case 'd':
	//derecha:
       azimut += k;
       break;
     case 'e':
       distancia += k;
       break;
     case 'q':
       distancia -= k;
       break;      	
  }
  
}

/**
 * Procesa las teclas especiales
 * Flechas de izq der arriba y abajo
 * Controlan el movimiento de un objeto
 */

void teclas_esp (int tecla, int x, int y){
  float k = 0.1;

  switch(tecla){
      case GLUT_KEY_UP:
	objetos[seleccion].z += k;
	break;
      case GLUT_KEY_LEFT:
	objetos[seleccion].x -= k;
	break;
      case GLUT_KEY_RIGHT:
	objetos[seleccion].x += k;

	break;
      case GLUT_KEY_DOWN:
	objetos[seleccion].z -= k;
	break;

  }
   glutPostRedisplay();

}

/**
 * Situa los objetos en pos. inicial
 */

void initObjetos(){

  objetos[1].x= 5;
  objetos[1].y= 0.4;
  objetos[1].z= 5;

}


/**
 * Funcion principal del programa
 */
int main (int argc, char** argv){

  //Inicializa la ventana
  glutInit(&argc,argv);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition (10, 50);
  glutCreateWindow("Visualizador de Modelos 3D");

  //Posicionamos las figuras
  initObjetos();
 
  //Dibujar escena
  glutDisplayFunc(display);

  //Dibujar acorde a cambios en ventana
  glutReshapeFunc(cambios_ventana);

  //Accion por defecto (al estar idle)
  glutIdleFunc(display);

  //Funcion que activa el input por teclado
  glutKeyboardFunc(teclado);
  glutSpecialFunc(teclas_esp);

  glEnable(GL_DEPTH_TEST);

  //Ejecutar todo
  glutMainLoop();

  return 0;
  

}
