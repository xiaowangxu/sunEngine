#pragma once

#include "sunEngine_Utility.h"
#include "engine_BehaviourManager.h"
extern Application App;
extern MouseObj Mouse;

namespace bh_Animater
{

enum Animation_Type
{
	Linear,QuadIn,QuadOut,CubicIn,CubicOut,BackIn,BackOut,ElasticIn,ElasticOut,CircleIn,CircleOut
};

enum Animation_Mode
{
	Once,Loop,PingPong
};

enum Animation_State
{
	Null,Playing,Ended
};

enum Animation_Bond
{
	Value,X,Y,Width,Height,Angle,Opacity,Size
};

enum Animation_StopMode
{
	Start,End,Current
};

} // namespace bh_Animatier

class Animater : public Behaviour
{
private:
	double Start,End,Duration,Value = 0;
	double CurrentTime = 0;
	bh_Animater::Animation_Bond Bond;
	bh_Animater::Animation_State State;
	bh_Animater::Animation_Type AnimationType;
	bh_Animater::Animation_Mode AnimationMode;
	bool isUpdated = false, SystemStopped = false;
	bh_Animater::Animation_State LastState = bh_Animater::Null;
	bool OnFinish = false;

	void TargetUpdate();
public:
	Animater();
	Animater(const string &name, double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Mode mode, bh_Animater::Animation_Bond target);
	void SetAnimation(double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Mode mode, bh_Animater::Animation_Bond target);
	void StartAnimation();
	void PauseAnimation();
	void StopAnimation(bh_Animater::Animation_StopMode mode);
	void ForceRestartAnimation();
	void ReverseAnimation();
	bool OnFinished() const;
	void AnimationUpdate();
	bh_Animater::Animation_State GetState() const;
	double GetValue();
	virtual void Update(engine_Graph &Target);
};

class MouseSensor : public Behaviour
{
private:
	bool isIn = false;
	Mouse_Button::Mouse_Button_State LastButtonState = Mouse_Button::Release;
	bool OnButtonClick = false;
	Mouse_Button::Mouse_Button ButtonClicked = Mouse_Button::None;
	bool isLastIn = false;
	bool RollIn = false,RollOut = false;
public:
	MouseSensor();
	bool MouseisIn() const;
	bool OnRollIn() const;
	bool OnRollOut() const;
	bool OnClick(const Mouse_Button::Mouse_Button button)const;
	virtual void Update(engine_Graph &Target);
};