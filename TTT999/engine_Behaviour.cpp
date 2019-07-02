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
	AnimationMode(bh_Animater::Once),
	Bond(bh_Animater::Value),
	isUpdated(false),
	State(bh_Animater::Null) {}

Animater::Animater(const string &name, double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Mode mode, bh_Animater::Animation_Bond target):
	Behaviour(name),
	Value(0),
	Start(start),
	End(end),
	Duration(duration),
	CurrentTime(0),
	AnimationType(type),
	AnimationMode(mode),
	Bond(target),
	isUpdated(false),
	State(bh_Animater::Null) {}
	
void Animater::SetAnimation(double start, double end, double duration, bh_Animater::Animation_Type type, bh_Animater::Animation_Mode mode, bh_Animater::Animation_Bond target)
{
	Value = 0;
	Start = start;
	End = end;
	Duration = duration;
	CurrentTime = 0;
	AnimationType = type;
	AnimationMode = mode;
	Bond = target;
	isUpdated = false;
	State = bh_Animater::Null;
}

void Animater::TargetUpdate()
{
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
	case bh_Animater::Size:
		this->GetTarget()->SetWidth(this->Value);
		this->GetTarget()->SetHeight(this->Value);
		break;
	default:
		break;
	}
}

void Animater::AnimationUpdate()
{
	//	On Finished
	if(LastState != State && State == bh_Animater::Ended)
	{
		this->OnFinish = true;
		//cout<<"On Animation Finished"<<endl;
	}
	else
	{
		this->OnFinish = false;
	}
	// Last State
	this->LastState = this->State;

	if( this->isUpdated || this->State == bh_Animater::Null || this->SystemStopped)	return;

	if (this->State == bh_Animater::Ended)
	{
		switch (this->AnimationMode)
		{
		case bh_Animater::Once:
			return;
			break;
		case bh_Animater::Loop:
			this->ForceRestartAnimation();
			return;
			break;
		case bh_Animater::PingPong:
			this->ReverseAnimation();
			this->ForceRestartAnimation();
			return;
			break;
		default:
			break;
		}
		return;
	}

	double t = CurrentTime / Duration;
	double tOut = 1.0 - t;

	switch (this->AnimationType)
	{
	case bh_Animater::Linear:
		this->Value = Start + (End - Start) * t;
		break;
	case bh_Animater::QuadIn:
		this->Value = Start + (End - Start) * t * t;
		break;
	case bh_Animater::QuadOut:
		this->Value = Start + (End - Start) * (1.0 - tOut * tOut);
		break;
	case bh_Animater::CubicIn:
		this->Value = Start + (End - Start) * t * t * t;
		break;
	case bh_Animater::CubicOut:
		this->Value = Start + (End - Start) * (1.0 - tOut * tOut * tOut);
		break;
	case bh_Animater::BackIn:
		this->Value = Start + (End - Start) * (t * t * t - 1 * t * sin(t * sunEngine::Pi));
		break;
	case bh_Animater::BackOut:
		this->Value = Start + (End - Start) * (1.0 - (tOut * tOut * tOut - 1 * tOut * sin(tOut * sunEngine::Pi)));
		break;
	case bh_Animater::ElasticIn:
		this->Value = Start + (End - Start) * ((t * t) * sin(4.5 * sunEngine::Pi * t));
		break;
	case bh_Animater::ElasticOut:
		this->Value = Start + (End - Start) * (1.0 - ((tOut * tOut) * sin(4.5 * sunEngine::Pi * tOut)));
		break;
	case bh_Animater::CircleIn:
		this->Value = Start + (End - Start) * (1.0 - sqrt(1.0 - t * t));
		break;
	case bh_Animater::CircleOut:
		this->Value = Start + (End - Start) * sqrt(1.0 - tOut * tOut);
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
		//cout << "Animation Ended" << endl;
	}
	else
	{
		this->CurrentTime += App.dt/1000.0;
		//cout<<"Time Updated "<<CurrentTime<<endl;
	}
	this->TargetUpdate();
}

void Animater::StartAnimation()
{
	if (this->State != bh_Animater::Playing)
	{
		this->State = bh_Animater::Playing;
		this->SystemStopped = false;
	}
}

void Animater::ForceRestartAnimation()
{
	this->SystemStopped = false;
	this->State = bh_Animater::Playing;
}

void Animater::PauseAnimation()
{
	if(this->State == bh_Animater::Playing)
	{
		this->State = bh_Animater::Null;
		this->SystemStopped = true;
	}
}

void Animater::StopAnimation(bh_Animater::Animation_StopMode mode)
{
	if(this->State == bh_Animater::Ended)	return;
	this->CurrentTime = 0;
	this->State = bh_Animater::Ended;
	this->SystemStopped = true;
	//cout<<"SystemStopped"<<endl;
	switch (mode)
	{
	case bh_Animater::Start:
		this->Value = this->Start;
		break;
	case bh_Animater::End:
		this->Value = this->End;
		break;
	case bh_Animater::Current:
		break;
	default:
		break;
	}
	this->TargetUpdate();
}

void Animater::ReverseAnimation()
{
	if (this->State != bh_Animater::Playing)
		this->CurrentTime = 0;
	double temp = this->Start;
	this->Start = this->End;
	this->End = temp;
	this->State = bh_Animater::Null;
}

bool Animater::OnFinished() const
{
	return this->OnFinish;
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
	this->isUpdated = false;
}

// MouseSensor
MouseSensor::MouseSensor() : Behaviour("NewAnimater"), isIn(false) {}

bool MouseSensor::MouseisIn() const
{
	return this->isIn;
}

bool MouseSensor::OnClick(const Mouse_Button::Mouse_Button button) const
{
	
	return this->OnButtonClick && (button == this->ButtonClicked);
}

bool MouseSensor::OnRollIn() const
{

	return this->RollIn;
}

bool MouseSensor::OnRollOut() const
{

	return this->RollOut;
}

void MouseSensor::Update(engine_Graph &Target)
{

	GLdouble DrawX, DrawY;

	switch (Target.GetAnchorPoint())
	{
	case sunEngine_Graph::Top:
	case sunEngine_Graph::TopLeft:
	case sunEngine_Graph::TopRight:
		DrawY = Target.GetPosition().Y - Target.GetSize().Y;
		break;
	case sunEngine_Graph::Left:
	case sunEngine_Graph::Center:
	case sunEngine_Graph::Right:
		DrawY = Target.GetPosition().Y - Target.GetSize().Y / 2;
		break;
	case sunEngine_Graph::BottomLeft:
	case sunEngine_Graph::Bottom:
	case sunEngine_Graph::BottomRight:
		DrawY = Target.GetPosition().Y;
		break;
	default:
		break;
	}

	switch (Target.GetAnchorPoint())
	{
	case sunEngine_Graph::Left:
	case sunEngine_Graph::TopLeft:
	case sunEngine_Graph::BottomLeft:
		DrawX = Target.GetPosition().X;
		break;
	case sunEngine_Graph::Top:
	case sunEngine_Graph::Center:
	case sunEngine_Graph::Bottom:
		DrawX = Target.GetPosition().X - Target.GetSize().X / 2;
		break;
	case sunEngine_Graph::BottomRight:
	case sunEngine_Graph::Right:
	case sunEngine_Graph::TopRight:
		DrawX = Target.GetPosition().X - Target.GetSize().X;
		break;
	default:
		break;
	}

	if (Mouse.Position.X >= DrawX && Mouse.Position.X <= DrawX + Target.GetSize().X && Mouse.Position.Y >= DrawY && Mouse.Position.Y <= DrawY + Target.GetSize().Y)
	{
		this->isIn = true;
	}
	else
	{
		this->isIn = false;
	}

	// Update Click
	if ((Mouse.State == Mouse_Button::Down && LastButtonState == Mouse_Button::Release) && isIn)
	{
		this->OnButtonClick = true;
		ButtonClicked = Mouse.Button;
		//cout << ButtonClicked << "On Clicked" << endl;
	}
	else
	{
		this->OnButtonClick = false;
	}

	// Update Roll In & Out
	if(isLastIn != isIn)
	{
		if(isLastIn)
		{
			this->RollOut = true;
			//cout<<"RollOut"<<endl;
		}
		else
		{
			this->RollIn = true;
			//cout << "RollIn" << endl;
		}
	}
	else
	{
		this->RollIn = false;
		this->RollOut = false;
	}


	// Next Tick
	this->LastButtonState = Mouse.State;
	this->isLastIn = isIn;

}