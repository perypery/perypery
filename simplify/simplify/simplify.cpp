#include <windows.h>
#include <glut.h>
#include <iostream>
#include <fstream>
#include "Vector3.h"
#include "Vector4.h"
#include "Object.h"
#include "Matrix4.h"
#include <stdarg.h>
#include <stdlib.h>
#include <iomanip>
#include "glm.h"

using namespace std;

char input_name[256];
char output_name[256];



GLfloat eye[3] = { 0.0, 0.0, 2.0 };
GLfloat at[3]  = { 0.0, 0.0, 0.0 };
GLfloat up[3]  = { 0.0, 1.0, 0.0 };

GLMmodel* pmodel = NULL;

void redisplay_all(void);
GLdouble projection[16], modelview[16], inverse[16];
GLuint window, world, screen, command;
GLuint sub_width = 256, sub_height = 256;
static float angleX=0.0,angleY=0.0;
int rx=0,ry=0,rz=0;
float px=0,py=0,pz=0;
float scale=1;
float lx=1;

GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess = 65.0;  
GLfloat light_position[]={ 1.0 , 1.0 , 1.0 , 1.0 };

void inputKey(unsigned char key, int x1, int y1) 
{
	switch (key) 
	{
        case GLUT_KEY_LEFT : 
					 angleX--;
					 if (angleX>360) angleX=0;                 
                      
						 break;
                 case GLUT_KEY_RIGHT : 
                          angleX++;
					 if (angleX<-360) angleX=0; 
                          
						  break;
                 case GLUT_KEY_UP : 
					 angleY--;
					 if (angleY>360) angleY=0; 
                          break;
                 case GLUT_KEY_DOWN : 
					angleY++;
					 if (angleY<-360) angleY=0; 
                          break;
				 case 'k' :
					px=px+0.1;
					break;
				 case 'h' :
					px=px-0.1;
					break;
				 case 'u' :
					py=py+0.1;
					break;
				 case 'j' :
					py=py-0.1;
					break;
				 case 'y' :
					pz=pz+0.1;
					break;
				 case 'i' :
					pz=pz-0.1;
					break;
				case 'n' :
					scale=1.01;
					glmScale(pmodel,scale);
					break;
				case 'm' :
					scale=0.99;
					glmScale(pmodel,scale);
					break;
				case 'z':
					return;
						 
  } redisplay_all();
}

void inputKey2(int key, int x1, int y1) 
{
	switch (key) 
	{
                 case GLUT_KEY_LEFT : 
					 angleX--;
					 if (angleX>360) angleX=0;                 
                      
						 break;
                 case GLUT_KEY_RIGHT : 
                          angleX++;
					 if (angleX<-360) angleX=0; 
                          
						  break;
                 case GLUT_KEY_UP : 
					 angleY--;
					 if (angleY>360) angleY=0; 
                          break;
                 case GLUT_KEY_DOWN : 
					angleY++;
					 if (angleY<-360) angleY=0; 
                          break;
				 } redisplay_all();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width/height, 1.0, 8.0);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1],up[2]);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	if (!pmodel) 
	{
        pmodel = glmReadOBJ(output_name);
        if (!pmodel) exit(0);
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 0.0);
    }
		light_position[0]=lx;
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);	


		glLightfv( GL_LIGHT0 , GL_POSITION , light_position ); 

		glPushMatrix();		
		glRotatef(angleX,   rx,  1,   rz);
		glRotatef(angleY,   1,    ry,   rz);
		glTranslatef(px, py, pz);
		glmDraw(pmodel, GLM_SMOOTH );//| GLM_MATERIAL);
		glPopMatrix();

	glFlush ();
    glutSwapBuffers();
}

//get the mouse commands
void Load_Obj(int value)
{
    char* name = 0;
    GLint params[2];
    switch (value) 
	{
    case 'o':
        name = input_name;
        break;
    case 'n':
        name = output_name;
        break;
	case 'w':
        glGetIntegerv(GL_POLYGON_MODE, params);
        if (params[0] == GL_FILL)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;
	case 'l':
		if(lx==1) lx=-1;
		else
			lx=1;
    break;
    }
    if (name) 
	{
        pmodel = glmReadOBJ(name);
        if (!pmodel) exit(0);
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 0.0);
    }
    redisplay_all();
}

void redisplay_all(void)
{
    glutPostRedisplay();
}

//调用OpenGL输出
void openglshow(int argc, char **argv)
{	
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(50, 50);
    glutInit(&argc, argv);
    glutCreateWindow("show");
    glutKeyboardFunc(inputKey);
	glutSpecialFunc(inputKey2);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
	glutCreateMenu(Load_Obj);
	glutAddMenuEntry("Show Old Model", 'o');
	glutAddMenuEntry("Show New Model", 'n');
	glutAddMenuEntry("Change WireFrame/Filled", 'w');
	glutAddMenuEntry("Change Lighting", 'l');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    redisplay_all();
    glutMainLoop();
}

void mysimplify(int argc,char **argv)
{
	float ratio;//简化比
	if(argc == 1)
	{
		cout<<"input_name"<<endl;
		cin>>input_name;
		cout<<"output_name"<<endl;
		cin>>output_name;
		cout<<"ratio"<<endl;
		cin>>ratio;
	}
	else 
	{
		strcpy(input_name,argv[1]);
		strcpy(output_name, argv[2]);
		sscanf(argv[3], "%f", &ratio);
	}
	 
	Object model;
	model.InitializeAll(input_name);
	int count =0;
	int opt_faces;
	opt_faces= (int)(model.sizeofvalidfaces * ratio);
	double to_m = model.sizeofvalidfaces;
	double to_count = model.sizeofvalidfaces-opt_faces;
	while (model.sizeofvalidfaces > opt_faces) 
	{
		model.DeleteVertex();//精简
	}
	model.Write(output_name);
}

int main(int argc, char **argv) 
{
	mysimplify(argc,argv);
	openglshow(argc,argv);//在网上查了些OPENGL的库，加了一些功能
	system("pause");
	return 0;
}