#pragma once

#include "engine_Graph.h"
#include <gl/glut.h>
#include <string>
#include <cmath>
using namespace std;
extern Application App;
extern MouseObj Mouse;
extern const GLdouble sunEngine::Pi;

namespace bh_Shape
{
	

} // namespace bh_Shape


class Shape : public engine_Graph
{
private:
	string Name;
	sunEngine_Graph::engine_Graph_AnchorPoint AnchorPoint = sunEngine_Graph::Center;
	Vector3<GLfloat> Color = Vector3<GLfloat>(1.0,1.0,1.0);
	int EdgeCount = 20;

public:
	Shape(const string &text = "NewText");
	void SetAnchorPoint(sunEngine_Graph::engine_Graph_AnchorPoint anchorpoint);
	void SetShape(const int edgecount,const GLfloat R,const GLfloat G,const GLfloat B);
	void SetEdgeCount(const int edgecount);
	void SetR(const GLfloat R);
	void SetG(const GLfloat G);
	void SetB(const GLfloat B);

	virtual sunEngine_Graph::engine_Graph_AnchorPoint GetAnchorPoint() const;
	virtual void Render();
};
