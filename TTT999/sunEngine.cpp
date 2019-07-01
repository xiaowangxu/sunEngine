#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;

// config your game setting in "sunEngine_Utility.h"
// to use Mouse Plugin globally
extern MouseObj Mouse;

// Put Your Game Object Here
Shape Square;
MouseSensor Sensor;

void game_Initialize()
{
	// the script here will only run once before the game start
	Square.SetShape(4,1.0,0.0,0.0);
	Square.SetPosition(960,540);
	Square.SetSize(100,100);
	Square.AddBehaviour(Sensor);
}

void game_MainLoop()
{
	// put your main game logic here
	if(Sensor.OnRollIn())
	{
		Square.SetAngle(45);
	}
	if(Sensor.OnRollOut())
	{
		Square.SetAngle(0);
	}
}