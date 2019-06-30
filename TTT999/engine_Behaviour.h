#pragma once

#include "sunEngine_Utility.h"
#include "engine_BehaviourManager.h"
extern Application App;
extern MouseObj Mouse;

namespace bh_Animater
{

enum Animation_Type
{
	Linear,Quadratic,Cubic,Random
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
	Value,X,Y,Width,Height,Angle,Opacity
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
	bool isUpdated = false;
public:
	Animater();
	Animater(const string &name, double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Mode mode, bh_Animater::Animation_Bond target);
	void SetAnimation(double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Mode mode, bh_Animater::Animation_Bond target);
	void StartAniamtion();
	void PauseAnimation();
	void StopAnimation(bh_Animater::Animation_StopMode mode);
	void ForceRestartAniamtion();
	void ReverseAniamtion();
	void AnimationUpdate();
	bh_Animater::Animation_State GetState() const;
	double GetValue();
	virtual void Update(engine_Graph &Target);
};

class MouseSensor : public Behaviour
{
private:
	bool isIn = false;

public:
	MouseSensor();
	bool MouseisIn() const;
	virtual void Update(engine_Graph &Target);
};