// Name: Robert Wyatt
// Quarter, Year: Winter 2021
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

vector<vec2> clicks;

void GL_render()
{
	float sumation_x = 0;
	float sumation_y = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINE_STRIP);
    
    glColor3f(1.0f,0.0f,0.0f);

if(clicks.size() > 1){
    float coefficents[clicks.size()];
    glVertex2f(clicks[0][0],clicks[0][1]);
    
    for(float t = 0.01; t <= 1; t = t + 0.01){
		sumation_x = 0;
		sumation_y = 0;
		for (unsigned int i = 0; i < clicks.size(); i++)
			coefficents[i]=1.0;
		for(unsigned int i = 1; i < clicks.size();i++){
			coefficents[i] = coefficents[i-1] * t * (clicks.size()-i)/i;
		}
		for(unsigned int i = clicks.size()-1; i >= 1;i--){
			coefficents[i-1] = coefficents[i] * (t-1); 
		}
		for(unsigned int i = 0; i < clicks.size(); i++){
			sumation_x = sumation_x + coefficents[i]*clicks[i][0];
			sumation_y = sumation_y + coefficents[i]*clicks[i][1];

		}

		glVertex2f(sumation_x,sumation_y);
	}
}


    glEnd();
    
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(1.0f,1.0f,0.0f);
    
    for(unsigned int i = 0; i < clicks.size();i++){
		glVertex2f(clicks[i][0],clicks[i][1]);
	}
    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        // TODO: the mouse click coordinates are (px,py).
        vec2 intoClick;
        intoClick[0] = (float)px;
        intoClick[1] = (float)py;
        clicks.push_back(intoClick);
        glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - <Insert Name Here>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
