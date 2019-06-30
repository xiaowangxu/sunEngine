#pragma once

#include <gl/glut.h>
#include "Vector.h"
#include <string>
#include <math.h>
using namespace std;

struct Application
{
	string Title = "NewGame";
	Vector2<int> WindowSize = Vector2<int>(360,640);
	Vector2<GLdouble> ViewportSize = Vector2<GLdouble>(720., 1280.);
	Vector2<GLdouble> Origin = Vector2<GLdouble>(0., 0.);
	Vector3<GLclampf> BgColor = Vector3<GLclampf>(0.0f, 0.0f, 0.0f);
	int dt = 17;
};

namespace Mouse_Button
{

enum Mouse_Button
{
	Left,Middle,Right
};

enum Mouse_Button_State
{
	Down,Release
};

};

struct MouseObj
{
	Vector2<GLdouble> Position;
	Mouse_Button::Mouse_Button Button;
	Mouse_Button::Mouse_Button_State State;
};

void MouseButton(int button, int state, int X, int Y);
void MousePosition(int X, int Y);

void WindowResize(int width, int height);

extern Application App;

GLdouble ViewportX_2_OGL(GLdouble Number);
GLdouble ViewportY_2_OGL(GLdouble Number);

namespace sunEngine
{

GLdouble Distance(GLdouble X1,GLdouble Y1,GLdouble X2,GLdouble Y2);

template <typename T>
T Clamp(T X,T Low,T Top)
{
	if(X < Low)		return Low;
	else if(X > Top)	return Top;
	else			return X;
}

GLdouble Lerp(GLdouble A,GLdouble B,GLdouble T);

const GLdouble Pi = 3.1415926;

};