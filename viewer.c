#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "glm.h"


float azimut = 0.78; //angulo theta
float elevacion = 0.78; //angulo fi
float distancia = 50.0; //radio esferico ro


/**
 *Dibuja la escena
 */ 
void display(){

  int i;

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

  //Sistema de Referencia

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

void control_camara (unsigned char tecla, int x, int y){

  /* Una fraccion del vector de
   * direccion de la camara 
   * (linea de observacion)
   */
  float k = 0.1;

  switch(tecla){
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
 * Funcion principal del programa
 */
int main (int argc, char** argv){

  //Inicializa la ventana
  glutInit(&argc,argv);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition (10, 50);
  glutCreateWindow("Visualizador de Modelos 3D");

 
  //Dibujar escena
  glutDisplayFunc(display);

  //Dibujar acorde a cambios en ventana
  glutReshapeFunc(cambios_ventana);

  //Accion por defecto (al estar idle)
  glutIdleFunc(display);

  //Funcion que activa el input por teclado
  glutKeyboardFunc(control_camara);

  glEnable(GL_DEPTH_TEST);

  //Ejecutar todo
  glutMainLoop();

  return 1;
  

}
