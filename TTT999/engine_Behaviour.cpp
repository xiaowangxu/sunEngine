#include "pch.h"
#include "engine_Behaviour.h"

// Animater
Animater::Animater():
	Behaviour("NewAnimater"),
	Value(0),
	Start(0),
	End(100),
	Duration(60),
	CurrentTime(0),
	AnimationType(bh_Animater::Linear),
	Bond(bh_Animater::Value),
	isUpdated(false),
	State(bh_Animater::Null) {}

Animater::Animater(const string &name, double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Bond target):
	Behaviour(name),
	Value(0),
	Start(start),
	End(end),
	Duration(duration),
	CurrentTime(0),
	AnimationType(type),
	Bond(target),
	isUpdated(false),
	State(bh_Animater::Null) {}

void Animater::SetAnimation(double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Bond target)
{
	Value = 0;
	Start = start;
	End = end;
	Duration = duration;
	CurrentTime = 0;
	AnimationType = type;
	Bond = target;
	isUpdated = false;
	State = bh_Animater::Null;
}

void Animater::AnimationUpdate()
{
	if (this->State == bh_Animater::Ended || this->State == bh_Animater::Null || this->isUpdated)	return;
	switch (this->AnimationType)
	{
	case bh_Animater::Linear:
		this->Value = Start + (End - Start) / Duration * CurrentTime;
		break;
	case bh_Animater::Quadratic:
		this->Value = Start + ((End - Start) / (Duration * Duration)) * CurrentTime * CurrentTime;
		break;
	case bh_Animater::Cubic:
		this->Value = Start + ((End - Start) / (Duration * Duration * Duration)) * CurrentTime * CurrentTime * CurrentTime;
		break;
	default:
		break;
	}
	this->isUpdated = true;
	if (this->CurrentTime >= this->Duration)
	{
		this->State = bh_Animater::Ended;
		this->CurrentTime = 0;
		this->Value = this->End;
	}
	else
	{
		this->CurrentTime += 1;
	}
}

void Animater::StartAniamtion()
{
	if (this->State != bh_Animater::Playing)
		this->CurrentTime = 0;
	this->State = bh_Animater::Playing;
}

void Animater::ReverseAniamtion()
{
	if (this->State != bh_Animater::Playing)
		this->CurrentTime = 0;
	double temp = this->Start;
	this->Start = this->End;
	this->End = temp;
	this->State = bh_Animater::Null;
}

bh_Animater::Animation_State Animater::GetState() const
{
	return this->State;
}

double Animater::GetValue()
{
	return this->Value;
}

void Animater::Update(engine_Graph &Target)
{
	this->AnimationUpdate();
	switch (this->Bond)
	{
	case bh_Animater::X:
		this->GetTarget()->SetX(this->Value);
		break;
	case bh_Animater::Y:
		this->GetTarget()->SetY(this->Value);
		break;
	case bh_Animater::Width:
		this->GetTarget()->SetWidth(this->Value);
		break;
	case bh_Animater::Height:
		this->GetTarget()->SetHeight(this->Value);
		break;
	case bh_Animater::Angle:
		this->GetTarget()->SetAngle(this->Value);
		break;
	case bh_Animater::Opacity:
		this->GetTarget()->SetOpacity(this->Value);
		break;
	default:
		break;
	}
	this->isUpdated = false;
}

Timer::Timer(const string &name, double duration):
	Behaviour(name),Duration(duration),State(bh_Timer::Idol){}

void Timer::StartTimer()
{
	this->State = bh_Timer::Counting;
}

bh_Timer::Timer_State Timer::GetState() const
{
	return this->State;
}

void Timer::Update(engine_Graph &Target)
{
	this->CurrentTime += 1;
	if(this->CurrentTime >= this->Duration)
	{
		this->State = bh_Timer::Ended;
	}
}