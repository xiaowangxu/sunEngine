#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;

// config your game setting in "sunEngine_Utility.h"
// to use Mouse Plugin globally
extern MouseObj Mouse;

// Put Your Game Object Here

Shape Circle;
Shape Square;
MouseSensor Sensor;

void game_Initialize()
{
	// the script here will only run once before the game start
	Square.SetShape(6,1.0,0.0,0.0);
	Square.SetPosition(960,540);
	Square.SetSize(200,200);
	Circle.SetShape(4, 0.0, 1.0, 0.0);
	Circle.SetPosition(960, 540);
	Circle.SetSize(200, 200);
	Square.AddBehaviour(Sensor);
}

void game_MainLoop()
{
	// put your main game logic here
	if(Sensor.OnRollIn()){
	Square.SetAngle(Square.GetAngle() + 15);
	Square.SetG(1.0);}
	if (Sensor.OnRollOut())
	{
		Square.SetAngle(Square.GetAngle() + 15);
		Square.SetG(0.0);
	}
}