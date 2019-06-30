#pragma once

#include "sunEngine_Utility.h"
#include "Vector.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include "engine_Plugin.h"
#include "engine_Behaviour.h"
using namespace std;
extern Application App;

void sunEngine_Initialize(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, App.ViewportSize.X, 0.0, App.ViewportSize.Y);
	glViewport(0.0, 0.0, App.WindowSize.X, App.WindowSize.Y);
	glutInitWindowSize(App.WindowSize.X, App.WindowSize.Y);
	glutCreateWindow(App.Title.data());
}

void game_Initialize();
void game_MainLoop();

void sunEngine_Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(App.BgColor.X, App.BgColor.Y, App.BgColor.Z, 1.0f);
	engine_Graph_Render();
	//cout<<"-- Render"<<endl;
	glutPostRedisplay();
	glutSwapBuffers();
}

void sunEngine_Tick(int dt)
{
	game_MainLoop();
	engine_Graph_Update();
	glutTimerFunc(App.dt, sunEngine_Tick, 1);
}

int main(int argc, char *argv[])
{
	sunEngine_Initialize(argc, argv);
	game_Initialize();
	glutDisplayFunc(&sunEngine_Render);
	glutMouseFunc(&MouseButton);
	glutMotionFunc(&MousePosition);
	glutPassiveMotionFunc(&MousePosition);
	glutReshapeFunc(&WindowResize);
	glutTimerFunc(App.dt, sunEngine_Tick, 1);
	glutMainLoop();
}