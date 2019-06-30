#include "pch.h"
#include "engine_Graph.h"
#include "engine_BehaviourManager.h"
using namespace std;
using namespace sunEngine_Graph;

// engine_Graph
engine_Graph::engine_Graph()
{
	engine_Graph_Buffer.push_back(this);
}

engine_Graph::~engine_Graph()
{
	int Count = engine_Graph_Buffer.size();
	for(int i = 0 ; i < Count ; i++)
	{
		if(engine_Graph_Buffer.at(i) == this)
		{
			engine_Graph_Buffer.erase(engine_Graph_Buffer.begin()+i);
		}
	}
}

void engine_Graph::SetX(const GLdouble Number)
{
	this->Position.X = Number;
}

void engine_Graph::SetY(const GLdouble Number)
{
	this->Position.Y = Number;
}

void engine_Graph::SetPosition(const GLdouble x, const GLdouble y)
{
	this->Position.X = x;
	this->Position.Y = y;
}

void engine_Graph::SetWidth(const GLdouble Number)
{
	this->Size.X = Number;
}

void engine_Graph::SetHeight(const GLdouble Number)
{
	this->Size.Y = Number;
}

void engine_Graph::SetSize(const GLdouble Width, const GLdouble Height)
{
	this->Size.X = Width;
	this->Size.Y = Height;
}

void engine_Graph::SetAngle(const GLdouble Ang)
{
	this->Angle = Ang;
}

void engine_Graph::SetVisible(const sunEngine_Graph::engine_Graph_Visible visible)
{
	this->Visible = visible;
}

void engine_Graph::SetOpacity(const GLclampf Opac)
{
	this->Opacity = Opac;
}

Vector2<GLdouble> engine_Graph::GetPosition()
{
	return this->Position;
}

Vector2<GLdouble> engine_Graph::GetSize()
{
	return this->Size;
}

GLclampf engine_Graph::GetOpacity()
{
	return this->Opacity;
}

GLdouble engine_Graph::GetAngle()
{
	return (this->Angle);
}

sunEngine_Graph::engine_Graph_Visible engine_Graph::GetVisibility()
{
	return (this->Visible);
}

void engine_Graph::AddBehaviour(Behaviour &behaviour)
{
	if(behaviour.GetTarget() != NULL)	return;
	this->TEST.push_back(&behaviour);
	behaviour.SetTarget(this);
}

void engine_Graph::UpdateBehaviour()
{
	for (int i = 0; i < this->TEST.size(); i++)
	{
		if (this->TEST.at(i)->isActive())
			this->TEST.at(i)->Update(*this);
	}
}

void engine_Graph::Render()
{}

// engine Render
vector<engine_Graph *> engine_Graph_Buffer;

void engine_Graph_Render()
{
	int Count = engine_Graph_Buffer.size();
	for (int i = 0; i < Count; i++)
	{
		engine_Graph_Buffer.at(i)->Render();
	}
}

void engine_Graph_Update()
{
	int Count = engine_Graph_Buffer.size();
	for (int i = 0; i < Count; i++)
	{
		engine_Graph_Buffer.at(i)->UpdateBehaviour();
	}
}

void engine_Graph_Buffer_PrintInfo(bool detail)
{
	int Count = engine_Graph_Buffer.size();
	if(detail)
	for (int i = 0; i < Count; i++)
	{
		cout<<"Graph"<<engine_Graph_Buffer.at(i)->GetPosition()<<endl;
	}
	cout<<"Totally "<<Count<<" Graphic Objects"<<endl;
}