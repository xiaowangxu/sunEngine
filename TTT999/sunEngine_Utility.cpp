#include "pch.h"
#include "sunEngine_Utility.h"

Application App;

MouseObj Mouse;

void MouseButton(int button, int state, int X, int Y)
{
	switch(button)
	{
	case 0:
		Mouse.Button = Mouse_Button::Left;
		break;
	case 1:
		Mouse.Button = Mouse_Button::Middle;
		break;
	case 2:
		Mouse.Button = Mouse_Button::Right;
		break;
	default:
		break;
	}
	switch (state)
	{
	case 0:
		Mouse.State = Mouse_Button::Down;
		break;
	case 1:
		Mouse.State = Mouse_Button::Release;
		break;
	default:
		break;
	}
}

void MousePosition(int X,int Y)
{
	Mouse.Position.X = ((GLdouble)X - App.Origin.X) / (GLdouble)App.WindowSize.X * App.ViewportSize.X;
	Mouse.Position.Y = (1.0 - ((GLdouble)Y - App.Origin.Y) / (GLdouble)App.WindowSize.Y) * App.ViewportSize.Y;
	//cout << "(" << X << "," <<Y << ")" << endl;
	//cout << "(" << Mouse.Position.X << "," << Mouse.Position.Y << ")" << endl;
}

void WindowResize(int w, int h)
{
	

	GLdouble CurrentRatio = (GLdouble)w / (GLdouble)h;
	GLdouble TargetRatio = App.ViewportSize.X / App.ViewportSize.Y;

	//cout<<"Current: "<<CurrentRatio<<" Target: "<<TargetRatio<<endl;

	if(CurrentRatio > TargetRatio)
	{
		glViewport(((GLdouble)w - h * TargetRatio)/2.0,0,h * TargetRatio,h);
		App.Origin.X = ((GLdouble)w - h * TargetRatio) / 2.0;
		App.Origin.Y = 0.0;
		App.WindowSize.X = h * TargetRatio;
		App.WindowSize.Y = h;
	}
	else
	{
		glViewport(0, ((GLdouble)h - w * 1.0 / TargetRatio) / 2.0, w,  w * 1.0/TargetRatio);
		App.Origin.X = 0.0;
		App.Origin.Y = ((GLdouble)h - w * 1.0 / TargetRatio) / 2.0;
		App.WindowSize.X = w;
		App.WindowSize.Y = w * 1.0 / TargetRatio;
	}
}

GLdouble ViewportX_2_OGL(GLdouble Number)
{
	return (Number / App.ViewportSize.X)*2.0 - 1.0;
}

GLdouble ViewportY_2_OGL(GLdouble Number)
{
	return (Number / App.ViewportSize.Y) * 2.0 - 1.0;
}

GLdouble sunEngine::Distance(GLdouble X1, GLdouble Y1, GLdouble X2, GLdouble Y2)
{
	return sqrt(pow(X1-X2,2.0)+pow(Y1-Y2,2.0));
}

GLdouble sunEngine::Lerp(GLdouble A, GLdouble B, GLdouble T)
{
	return A+(B-A)*T;
}