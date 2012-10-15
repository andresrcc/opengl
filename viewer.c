#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "glm.h"


float azimut = 0.78; //theta
float elevacion = 0.78; //fi
float distancia = 5.0; //ro


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
  
  //IMPORTANTE
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Situamos la camara

  //gluLookAt(10.0,10.0,10.0,20.0,0.0,0.0,0.0,1.0,0.0);

  gluLookAt(distancia * sin(elevacion) * sin(azimut),
	    distancia * cos(elevacion),
	    distancia * sin(elevacion) * cos(azimut),
	    0.0,0.0,0.0,
	    0.0,1.0,0.0);
  //Dibujamos el sistema de coordenadas

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
    if (i==0){
      glColor3f(.6,.3,.3);
    }else{
      glColor3f(.25,.25,.25);
    };

    glVertex3f(i,0,-10);
    glVertex3f(i,0,10);
    
    if (i==0){ 
      glColor3f(.3,.3,.6);
    }else{
      glColor3f(.25, .25, .25);
    };

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
    if (i==0){
      glColor3f(.6,.3,.3);
    }else{
      glColor3f(.25,.25,.25);
    };

    glVertex3f(i,-10,0);
    glVertex3f(i,10,0);
    
    if (i==0){ 
      glColor3f(.3,.3,.6);
    }else{
      glColor3f(.25, .25, .25);
    };

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
    if (i==0){
      glColor3f(.6,.3,.3);
    }else{
      glColor3f(.25,.25,.25);
    };

    glVertex3f(0.0,-10.0,i);
    glVertex3f(0.0,10.0,i);
    
    if (i==0){ 
      glColor3f(.3,.3,.6);
    }else{
      glColor3f(.25, .25, .25);
    };

    glVertex3f(0.0,i,-10);
    glVertex3f(0.0,i,10);

  };

  glEnd();
  
  // glFlush();
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

void moverse (unsigned char tecla, int x, int y){

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
  glutCreateWindow("viewer");

 
  //Dibujar escena
  glutDisplayFunc(display);

  //Dibujar acorde a cambios en ventana
  glutReshapeFunc(cambios_ventana);

  //Accion por defecto (al estar idle)
  glutIdleFunc(display);

  //Funcion que activa el input por teclado
  glutKeyboardFunc(moverse);

  glEnable(GL_DEPTH_TEST);

  //Ejecutar todo
  glutMainLoop();

  return 1;
  

}
