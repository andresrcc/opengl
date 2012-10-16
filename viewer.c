#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "glm.h"

/**
 * Variables Globales
 */

//Coordeadas de la Camara
float azimut = 0.78; 
float elevacion = 0.78;
float distancia = 50.0;

//Objetos

//--Para importar .obj
GLMmodel *modelo = NULL;

//--Para moverlo--


struct objeto{
  int n;
  int x;
  int y;
  int z;

  struct objeto *proximo;

};

struct objeto *raiz;
struct objeto *objetos;


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
 * Funcion para crear nuevos
 * objetos los cuales luego
 * seran agregados con la
 * funcion agregar objetos
 */
void crear_objeto(n,x,y,z){

    /* Creamos espacio para el objeto en
   * la lista enlazada
   */
  while (objetos->proximo != 0){
    objetos = objetos->proximo;
  }
  objetos->proximo = malloc(sizeof(struct objeto));

  objetos->proximo->n = objetos->n ++;

  objetos = objetos->proximo;

  objetos->n = n;
  objetos->x = x;
  objetos->y = y;  
  objetos->z = z;
  objetos->proximo = 0;
}

/**
 * Agrega objetos ya creados
 * al modelo
 */

void agregar_objeto(char *path_archivo){

  //Guardamos su localizacion
  crear_objeto(5,1,5);

  glPushMatrix();

  glTranslatef(5,1,5);
  glColor3f(.3,.4,.3);

  modelo = glmReadOBJ(path_archivo);
  if (!modelo) exit (0); //si no existe, exit

  glmUnitize(modelo);
  glmFacetNormals(modelo);
  glmVertexNormals(modelo, 90.0);

  glmDraw(modelo, GLM_SMOOTH | GLM_MATERIAL);
  
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
  sistema_referencia();

  //Agregamos objetos al modelo
  agregar_objeto("objetos/porsche.obj");
  
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

void movimiento (unsigned char tecla, int x, int y){

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

  //Inicializa lista de objetos
  raiz = malloc(sizeof(struct objeto));
  raiz->n = 0;
  raiz->x = 0;
  raiz->y = 0;
  raiz->z = 0;
  raiz->proximo = 0;  
  objetos = raiz;

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
  glutKeyboardFunc(movimiento);

  glEnable(GL_DEPTH_TEST);

  //Ejecutar todo
  glutMainLoop();

  return 1;
  

}
