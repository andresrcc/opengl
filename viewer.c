#include <stdio.h>
#include <GL/glut.h>

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

  gluLookAt(3.0,3.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
  //Dibujamos el sistema de coordenadas

  glColor3f(.3, .3, .3);
  //Malla del plano x-z 

   //Rectangulo
  glBegin(GL_QUADS); 
  glVertex3f( 0, -0.001, 0);
  glVertex3f( 0, -0.001, 20);
  glVertex3f( 20, -0.001, 20);
  glVertex3f( 20, -0.001, 0);
  glEnd();

   //Lineas de la malla
  glBegin(GL_LINES);
  for (i=0; i<=20; i++){
    if (i==0){
      glColor3f(.6,.3,.3);
    }else{
      glColor3f(.25,.25,.25);
    };

    glVertex3f(i,0,0);
    glVertex3f(i,0,20);
    
    if (i==0){ 
      glColor3f(.3,.3,.6);
    }else{
      glColor3f(.25, .25, .25);
    };

    glVertex3f(0,0,i);
    glVertex3f(20,0,i);

  };
  glEnd();

  //Maya del plano x-y
  glColor3f(.5, .2, .4);
  glBegin(GL_QUADS); 
  glVertex3f( 0.0, -0.001, 0.0);
  glVertex3f( 20, -0.001, 0);
  glVertex3f( 20, 20, -0.001);
  glVertex3f( 0.0, 20, 0.0);
  glEnd();

  glBegin(GL_LINES);
  for (i=0; i<=20; i++){
    if (i==0){
      glColor3f(.6,.3,.3);
    }else{
      glColor3f(.25,.25,.25);
    };

    glVertex3f(i,0,0);
    glVertex3f(i,20,0);
    
    if (i==0){ 
      glColor3f(.3,.3,.6);
    }else{
      glColor3f(.25, .25, .25);
    };

    glVertex3f(0,i,0);
    glVertex3f(20,i,0);

  };

  glEnd();


  //Maya del plano z-y
  glColor3f(.3, .3, .2);
  glBegin(GL_QUADS); 
  glVertex3f( 0.0, -0.001, 0.0);
  glVertex3f( 0, -0.001, 20);
  glVertex3f( -0.001, 20, 20);
  glVertex3f( 0.0, 20, 0.0);
  glEnd();

  glBegin(GL_LINES);
  for (i=0; i<=20; i++){
    if (i==0){
      glColor3f(.6,.3,.3);
    }else{
      glColor3f(.25,.25,.25);
    };

    glVertex3f(0,0,i);
    glVertex3f(0,20,i);
    
    if (i==0){ 
      glColor3f(.3,.3,.6);
    }else{
      glColor3f(.25, .25, .25);
    };

    glVertex3f(0,i,0);
    glVertex3f(0,i,20);

  };

  glEnd();
  
  glFlush();
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
 * Funcion principal del programa
 */
int main (int argc, char** argv){

  //Inicializa la ventana
  glutInit(&argc,argv);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition (10, 50);
  glutCreateWindow("viewer");

  /* Debo Incluirlos?
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  //glEnable(GL_LIGHTING);
  */


  //Dibujar escena
  glutDisplayFunc(display);

  //Dibujar acorde a cambios en ventana
  glutReshapeFunc(cambios_ventana);


  //Ejecutar todo
  glutMainLoop();

  return 0;
  

}