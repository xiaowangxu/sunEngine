#pragma once

#include "sunEngine_Utility.h"
#include <iostream>
#include <string>
#include <vector>
#include "Vector.h"
using namespace std;
extern Application App;

class Behaviour;

namespace sunEngine_Graph
{
enum engine_Graph_AnchorPoint
{
	TopLeft,
	Top,
	TopRight,
	Left,
	Center,
	Right,
	BottomLeft,
	Bottom,
	BottomRight
};

enum engine_Graph_Visible
{
	Invisible,Visible
};

} // namespace sunEngine_Graph

class engine_Graph
{
private:
	Vector2<GLdouble> Position = Vector2<GLdouble>(0, 0);
	GLdouble Angle = 0.0;
	Vector2<GLdouble> Size = Vector2<GLdouble>(100, 100);
	GLfloat Opacity = 1.0f;
	sunEngine_Graph::engine_Graph_Visible Visible = sunEngine_Graph::Visible;
	vector<Behaviour *> TEST;
public:
	engine_Graph();
	virtual ~engine_Graph();

	void SetX(const GLdouble Number);
	void SetY(const GLdouble Number);

	void SetPosition(const GLdouble x, const GLdouble y);

	void SetWidth(const GLdouble Number);
	void SetHeight(const GLdouble Number);

	void SetSize(const GLdouble Width, const GLdouble Height);

	void SetOpacity(const GLfloat Opac);

	void SetAngle(const GLdouble Ang);

	void SetVisible(const sunEngine_Graph::engine_Graph_Visible visible);

	void AddBehaviour(class Behaviour &behaviour);

	Vector2<GLdouble> GetPosition();
	Vector2<GLdouble> GetSize();
	GLfloat GetOpacity();
	GLdouble GetAngle();
	sunEngine_Graph::engine_Graph_Visible GetVisibility();

	void UpdateBehaviour();
	virtual sunEngine_Graph::engine_Graph_AnchorPoint GetAnchorPoint() const;
	virtual void Render();
};

// Graphic Buffer
extern vector<engine_Graph *> engine_Graph_Buffer;

void engine_Graph_Render();
void engine_Graph_Update();
void engine_Graph_Buffer_PrintInfo(bool detail);