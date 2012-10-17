#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "glm.h"
//#include <string.h>
//#include <stdint.h>

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
GLMmodel *modelo_CARRO = NULL;
GLMmodel *modelo_AVION = NULL;
//--Para moverlo--


static GLdouble xant = 0.0, yant = 0.0;
static GLint mouse_action = 0;

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

void dibujar_objetos(){

  glEnable(GL_LIGHTING);
  //Dibujamos
  glPushMatrix();
  glTranslatef(objetos[1].x,objetos[1].y,objetos[1].z);
  glColor3f(2,8,3);

  //modelo = glmReadOBJ(path_archivo);
  //if (!modelo) exit (0); //si no existe, exit

  glmUnitize(modelo_CARRO);
  glmFacetNormals(modelo_CARRO);
  glmVertexNormals(modelo_CARRO, 90.0);
  glEnable(GL_COLOR_MATERIAL);
  glmDraw(modelo_CARRO, GLM_SMOOTH | GLM_MATERIAL);
  glDisable(GL_COLOR_MATERIAL);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(objetos[2].x,objetos[2].y,objetos[2].z);
  glColor3f(2,8,3);
  
  glmUnitize(modelo_AVION);
  glmFacetNormals(modelo_AVION);
  glmVertexNormals(modelo_AVION, 90.0);
  glEnable(GL_COLOR_MATERIAL);
  glmDraw(modelo_AVION, GLM_SMOOTH | GLM_MATERIAL);
  glDisable(GL_COLOR_MATERIAL);
  glPopMatrix();
  glDisable(GL_LIGHTING);

}

GLvoid mouseAction(GLint button, GLint state, GLint x, GLint y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			mouse_action = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			mouse_action =2;
			break;
	}
}

GLvoid mouseMove(GLint x, GLint y){
	float k = 0.01;
	float kz = 0.5;
	if (mouse_action == 1){
		if(x-xant>0.0){
			azimut += k;	
		}else if(x-xant<0.0){
			azimut -= k;
		}
		if(y-yant>0.0){
			elevacion -= k;
		}else if(y-yant<0.0){
			elevacion += k;
		}
	}else if(mouse_action == 2){
		if(y-yant>0.0){
			distancia += kz;
		}else if(y-yant<0.0){
			distancia -= kz;
		}
	}
	xant = x;
	yant = y;	

  

}


void loadBMP(char * imagepath){
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
	FILE * file = fopen(imagepath, "rb");
	if (fread(header,1,54,file)!=54){
//		return false;
	}
	if (header[0]!='B' || header[1]!='M'){
//		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if(imageSize==0){
		imageSize = width*height*3;
	}	
	if(dataPos == 0){
		dataPos = 54;
	}
	data = (unsigned char*)malloc(imageSize*sizeof(unsigned char));
	fread(data,1,imageSize,file);
	fclose(file);
	GLuint textureID;
	glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	



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
	
	//loadBMP("t2.bmp");


	anch = anch/2;
	alt = alt/2;
	prof = prof/2;
	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glNormal3f(0.0f,1.0f,0.0f);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(anch,prof,alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(anch,prof,-alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(-anch,prof,-alt);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(-anch,prof,alt);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(1.0f,0.0f,0.0f);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(anch,prof,alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(anch,prof,-alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(anch,-prof,-alt);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(anch,-prof,alt);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(0.0f,-1.0f,0.0f);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(anch,-prof,alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(anch,-prof,-alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(-anch,-prof,-alt);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(-anch,-prof,alt);
	glEnd();
	glBegin(GL_QUADS);
		glNormal3f(-1.0f,0.0f,0.0f);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(-anch,-prof,alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(-anch,-prof,-alt);
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(-anch,prof,-alt);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(-anch,prof,alt);
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
		//glTexCoord2f(0.0f,0.0f);
		glVertex3f(-anch,prof,-alt);
		//glTexCoord2f(1.0f,0.0f);
		glVertex3f(anch,prof,-alt);
		//glTexCoord2f(1.0f,1.0f);
		glVertex3f(anch,-prof,-alt);
		//glTexCoord2f(0.0f,1.0f);
		glVertex3f(-anch,-prof,-alt);
	glEnd();

	//glDisable(GL_TEXTURE_2D);
}


void dibujar_Joe(){

  //in vec2 UV;

  
  //Matriz mayor
  glPushMatrix();
  //trasladar todo el objeto
  glTranslatef(objetos[3].x,objetos[3].y,objetos[3].z);
  //Submatrices del objeto
  //Cabeza
  glColor3f(1.0f,1.0f,1.0f);
  glPushMatrix();
 	 glTranslatef(0,0.75,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.5,0.5,0.5);
  glPopMatrix();
  //torso
  //glColor3f(1.0,0,1.0);		
  glPushMatrix();	
 	 glTranslatef(0,0,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.3,0.15,1);
  glPopMatrix();
  //BrazoI
  //glColor3f(1.0,1.0,0);		
  glPushMatrix();	
 	 glTranslatef(0.35,0.2,-0.15);
  	 glRotatef(45.0,0,1.0,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.45,0.1,0.1);
  glPopMatrix();
  //BrazoD
  //glColor3f(1.0,1.0,0);		
  glPushMatrix();	
 	 glTranslatef(-0.35,0.2,-0.15);
	 glRotatef(-45.0,0,1.0,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.45,0.1,0.1);
  glPopMatrix();
  //PiernaI
 //glColor3f(0,1.0,1.0);		
  glPushMatrix();	
 	 glTranslatef(0.15,-0.5,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.1,0.1,0.5);
  glPopMatrix();
  //PiernaD
 //glColor3f(0,1.0,1.0);		
  glPushMatrix();	
 	 glTranslatef(-0.15,-0.5,0);
 	 dibujar_cubo(0.0,0.0,0.0,0.1,0.1,0.5);
  glPopMatrix();

  glPopMatrix();

}

/**
 * Dibuja la flecha de seleccion
 */

void dibujar_flecha(){

  glPushMatrix();
  glTranslatef(objetos[seleccion].x-2,
	       objetos[seleccion].y,
	       objetos[seleccion].z);
  glBegin(GL_TRIANGLES);
     glVertex3f(1.0,3.0,0.0);
     glVertex3f(3.0,3.0,0.0);
     glVertex3f(2.0,2.0,0.0);
  glEnd();
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
  //agregar_objeto("objetos/porsche.obj",1);
  //agregar_objeto("objetos/f-16.obj",2);
  dibujar_objetos();
//Jorge
  //Objeto propio
  dibujar_Joe();

  //Flecha de seleccion
  dibujar_flecha();

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
     case '3':
       seleccion = 3;
       break;
     case '1':
       seleccion = 1;
       break;
     case '2':
       seleccion = 2;
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
	objetos[seleccion].z -= k;
	break;
      case GLUT_KEY_LEFT:
	objetos[seleccion].x -= k;
	break;
      case GLUT_KEY_RIGHT:
	objetos[seleccion].x += k;

	break;
      case GLUT_KEY_DOWN:
	objetos[seleccion].z += k;
	break;

  }
   glutPostRedisplay();

}

/**
 * Situa los objetos en pos. inicial
 */

void initObjetos(){

  
  //Porsche 
  objetos[1].x= 5;
  objetos[1].y= 0.4;
  objetos[1].z= 5;

  //F-16 (Avion)
  objetos[2].x = -5;
  objetos[2].y = 0.4;
  objetos[2].z = 5;

  //objeto propio (joe)
  objetos[3].x = 5; 
  objetos[3].y = 0.75;
  objetos[3].z = -5;

}


/**
 * Funcion principal del programa
 */
int main (int argc, char** argv){
  static const GLfloat ambient[4] = {1.0f,1.0f,1.0f,1.0f,1.0f};
  //Inicializa la ventana
  glutInit(&argc,argv);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition (10, 50);
  glutCreateWindow("Visualizador de Modelos 3D");
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHTING);
  //Posicionamos las figuras
  initObjetos();
  modelo_CARRO = glmReadOBJ("objetos/porsche.obj");
  if (!modelo_CARRO) exit (0); //si no existe, exit
  modelo_AVION = glmReadOBJ("objetos/f-16.obj");
  if (!modelo_AVION) exit (0); //si no existe, exit
  //Dibujar escena
  glutDisplayFunc(display);

  //Dibujar acorde a cambios en ventana
  glutReshapeFunc(cambios_ventana);

  //Accion por defecto (al estar idle)
  glutIdleFunc(display);

  //Funcion que activa el input por teclado
  glutKeyboardFunc(teclado);
  glutSpecialFunc(teclas_esp);
  glutMotionFunc(mouseMove);
  glutMouseFunc(mouseAction);

  glEnable(GL_DEPTH_TEST);

//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glOrtho(-2.0,2.0,-2.0,2.0,-100.0,100.0);

  //Ejecutar todo
  glutMainLoop();

  return 0;
  

}
