#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;

// config your game setting in "sunEngine_Utility.h"
// to use Mouse Plugin globally
extern MouseObj Mouse;

// Put Your Game Object Here
class AnimationTest
{
public:
	Shape Circle;
	Animater Tween;

	AnimationTest()
	{
		Circle.SetShape(4, 1.0, 0.0, 0.0);
		Circle.SetSize(100, 100);
		Circle.AddBehaviour(Tween);
	}
};

AnimationTest Test[11];

void game_Initialize()
{
	// the script here will only run once before the game start
	for(int i=0;i<11;i++)
	{
		Test[i].Circle.SetPosition(200+150*i,0);
		Test[i].Circle.SetR(0.4 + 0.05*i);
		switch (i)
		{
		case 0:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::Linear, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 1:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::QuadIn, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 2:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::QuadOut, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 3:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::CubicIn, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 4:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::CubicOut, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 5:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::BackIn, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 6:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::BackOut, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 7:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::ElasticIn, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 8:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::ElasticOut, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 9:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::CircleIn, bh_Animater::PingPong, bh_Animater::Y);
			break;
		case 10:
			Test[i].Tween.SetAnimation(300, 780, 3, bh_Animater::CircleOut, bh_Animater::PingPong, bh_Animater::Y);
			break;
		default:
			break;

		}
		Test[i].Tween.StartAnimation();
	}
}

void game_MainLoop()
{
	// put your main game logic here
	/* if (Sensor.OnRollIn())
	{
		Test.PauseAnimation();
		//cout<<"Angle: "<<Square.GetAngle()<<endl;
	}
	if (Sensor.OnRollOut())
	{
		Test.StartAniamtion();
		//cout << "Angle: " << Square.GetAngle() << endl;
	} */
	if(MouseOnClick(Mouse_Button::Left))
	{
		cout<<"Left Clicked"<<endl;
	}
	if (MouseOnClick(Mouse_Button::	Right))
	{
		cout << "Right Clicked" << endl;
	}
	if (MouseOnClick(Mouse_Button::Middle))
	{
		cout << "Middle Clicked" << endl;
	}
}