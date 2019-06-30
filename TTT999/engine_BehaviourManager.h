#pragma once

#include "sunEngine_Utility.h"
#include <string>
#include <iostream>
#include "engine_Graph.h"
using namespace std;
extern Application App;

namespace sunEngine_Behaviour
{

enum engine_Behaviour_Active
{
	Deactive,Active
};

}; // namespace sunEngine_Behaviour

class Behaviour
{
private:
	string Name;
	bool Active = sunEngine_Behaviour::Active;
	engine_Graph *Target = NULL;
public:
	Behaviour(const string &name = "NewBehaviour");
	void SetTarget(engine_Graph *target);
	engine_Graph *GetTarget()const;
	void SetActive(sunEngine_Behaviour::engine_Behaviour_Active &activecode);
	bool isActive()const;
	virtual ~Behaviour();
	virtual void Update(engine_Graph &target);
};