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

enum Animation_State
{
	Null,Playing,Ended
};

enum Animation_Bond
{
	Value,X,Y,Width,Height,Angle,Opacity
};

} // namespace bh_Animatier

class Animater : public Behaviour
{
private:
	double Start,End,Duration,Value = 0;
	double CurrentTime;
	bh_Animater::Animation_Bond Bond;
	bh_Animater::Animation_State State;
	bh_Animater::Animation_Type AnimationType;
	bool isUpdated = false;
public:
	Animater();
	Animater(const string &name, double start, double end, double duration, bh_Animater::Animation_Type type,bh_Animater::Animation_Bond target);
	void SetAnimation(double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Bond target);
	void StartAniamtion();
	void ReverseAniamtion();
	void AnimationUpdate();
	bh_Animater::Animation_State GetState() const;
	double GetValue();
	virtual void Update(engine_Graph &Target);
};

namespace bh_Timer
{

enum Timer_State
{
	Idol,Counting,Ended
};

};

class Timer : public Behaviour
{
private:
	double Duration = 100,CurrentTime = 0;
	bh_Timer::Timer_State State = bh_Timer::Idol;
public:
	Timer(const string &name, double duration);
	void StartTimer();
	bh_Timer::Timer_State GetState() const;
	virtual void Update(engine_Graph &Target);
};