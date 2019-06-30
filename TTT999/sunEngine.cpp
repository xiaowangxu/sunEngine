#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;
extern MouseObj Mouse;

// Put Your Game Object Here

class TEST
{
public:
	Shape Square;
	Animater ChangeR;
	Vector2<GLdouble> Origin;

	TEST()
	{
		Square.SetAnchorPoint(sunEngine_Graph::Center);
		Square.SetSize(40,40);
		ChangeR.SetAnimation(0, (rand()%100)/100.0, 120, bh_Animater::Linear, bh_Animater::Value);
		Square.AddBehaviour(ChangeR);
		ChangeR.StartAniamtion();
	}

	void Update()
	{
		Square.SetAngle(Square.GetAngle()+0.1);
		Square.SetEdgeCount(int(sunEngine::Distance(Mouse.Position.X, Mouse.Position.Y, Square.GetPosition().X, Square.GetPosition().Y) / 10)%10);
		ChangeR.AnimationUpdate();
		Square.SetR(ChangeR.GetValue());
		Square.SetG(ChangeR.GetValue());
		if(ChangeR.GetState() == bh_Animater::Ended)
		{
			ChangeR.ReverseAniamtion();
			ChangeR.StartAniamtion();
		}
		if(Mouse.Button == Mouse_Button::Middle && Mouse.State == Mouse_Button::Down)
			Square.SetPosition(sunEngine::Lerp(Square.GetPosition().X, Mouse.Position.X,0.3),
							   sunEngine::Lerp(Square.GetPosition().Y, Mouse.Position.Y,0.3));
		else
			Square.SetPosition(sunEngine::Lerp(Square.GetPosition().X, Origin.X, 0.1),
							   sunEngine::Lerp(Square.GetPosition().Y, Origin.Y, 0.1));

		
			Square.SetSize(
				sunEngine::Clamp(sunEngine::Distance(Mouse.Position.X, Mouse.Position.Y, Square.GetPosition().X, Square.GetPosition().Y) / 10, (GLdouble)10, (GLdouble)40),
				sunEngine::Clamp(sunEngine::Distance(Mouse.Position.X, Mouse.Position.Y, Square.GetPosition().X, Square.GetPosition().Y) / 10, (GLdouble)10, (GLdouble)40));
	}

};

const int Count = 32;

TEST Obj[18][Count];

Shape *Center;

void game_Initialize()
{
	for(int i=0;i<18;i++)
	{
		for (int j = 0; j < Count; j++)
		{
			Obj[i][j].Square.SetPosition(20+40*i,20+40*j);
			Obj[i][j].Origin = Vector2<GLdouble>(20 + 40 * i,20+40*j);
		}
	}
}

void game_MainLoop()
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < Count; j++)
		{
			Obj[i][j].Update();
		}
	}

	if (Center == NULL && Mouse.Button == Mouse_Button::Left && Mouse.State == Mouse_Button::Down)
	{
		Center = new Shape;
		Center->SetShape(6, 1.0, 0.0, 0.0);
		Center->SetPosition(Mouse.Position.X, Mouse.Position.Y);
		Center->SetSize(100, 100);
		engine_Graph_Buffer_PrintInfo(false);
	}
	if (Center != NULL && Mouse.Button == Mouse_Button::Right && Mouse.State == Mouse_Button::Down)
	{
		delete Center;
		Center = NULL;
		engine_Graph_Buffer_PrintInfo(false);
	}
}