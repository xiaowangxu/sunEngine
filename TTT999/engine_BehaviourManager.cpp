#include "pch.h"
#include "engine_BehaviourManager.h"
#include "engine_Graph.h"
#include <iostream>

Behaviour::Behaviour(const string &name) : Name(name), Active(sunEngine_Behaviour::Active)
{
}

void Behaviour::SetTarget(engine_Graph *target)
{
	this->Target = target;
}

engine_Graph *Behaviour::GetTarget() const
{
	return this->Target;
}

void Behaviour::SetActive(sunEngine_Behaviour::engine_Behaviour_Active &activecode)
{
	this->Active = activecode;
}

bool Behaviour::isActive() const
{
	return this->Active;
}

void Behaviour::Update(engine_Graph &target)
{
	//std::cout << ">>Behaviour:" << this->Name << "\n";
}

Behaviour::~Behaviour()
{
	//std::cout<<"Behaviour:  "<<this->Name<<" Destroyed";
}