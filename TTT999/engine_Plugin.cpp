#include "pch.h"
#include "engine_Plugin.h"

Shape::Shape(const string &text) : Name(text) {}

void Shape::SetShape(const int edgecount,const GLfloat R,const GLfloat G,const GLfloat B)
{
	this->SetR(R);
	this->SetG(G);
	this->SetB(B);
	this->SetEdgeCount(edgecount);
}

void Shape::SetEdgeCount(const int edgecount)
{
	if(edgecount <=2)
	{
		this->EdgeCount = 3;
		return;
	}
	else
	{
		this->EdgeCount = edgecount;
		return;
	}
}

void Shape::SetColor(const GLfloat R, const GLfloat G, const GLfloat B)
{
	SetR(R);
	SetG(G);
	SetB(B);
}

void Shape::SetR(const GLfloat R)
{
	if(R > 1.0)
	{
		this->Color.X = 1.0;
		return;
	}
	else if(R < 0.0)
	{
		this->Color.X = 0.0;
		return;
	}
	else
	{
		this->Color.X = R;
		return;
	}
}

void Shape::SetG(const GLfloat G)
{
	if(G > 1.0)
	{
		this->Color.Y = 1.0;
		return;
	}
	else if(G < 0.0)
	{
		this->Color.Y = 0.0;
		return;
	}
	else
	{
		this->Color.Y=G;
		return;
	}
}

void Shape::SetB(const GLfloat B)
{
	if(B > 1.0)
	{
		this->Color.Z = 1.0;
		return;
	}
	else if(B < 0.0)
	{
		this->Color.Z = 0.0;
		return;
	}
	else
	{
		this->Color.Z=B;
		return;
	}
}

void Shape::SetAnchorPoint(sunEngine_Graph::engine_Graph_AnchorPoint anchorpoint)
{
	this->AnchorPoint = anchorpoint;
}

Vector3<GLfloat> Shape::GetColor() const
{
	return this->Color;
}

int Shape::GetEdgeCount() const
{
	return this->EdgeCount;
}

sunEngine_Graph::engine_Graph_AnchorPoint Shape::GetAnchorPoint() const
{
	return this->AnchorPoint;
}

void Shape::Render()
{
	if(this->GetVisibility() == sunEngine_Graph::Invisible)	return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(Color.X, Color.Y, Color.Z,GetOpacity());
	GLdouble DrawX,DrawY;

	switch (AnchorPoint)
	{
	case sunEngine_Graph::Top:
	case sunEngine_Graph::TopLeft:
	case sunEngine_Graph::TopRight:
		DrawY = GetPosition().Y - GetSize().Y;
		break;
	case sunEngine_Graph::Left:
	case sunEngine_Graph::Center:
	case sunEngine_Graph::Right:
		DrawY = GetPosition().Y - GetSize().Y/2;
		break;
	case sunEngine_Graph::BottomLeft:
	case sunEngine_Graph::Bottom:
	case sunEngine_Graph::BottomRight:
		DrawY = GetPosition().Y;
		break;
	default:
		break;
	}

	switch (AnchorPoint)
	{
	case sunEngine_Graph::Left:
	case sunEngine_Graph::TopLeft:
	case sunEngine_Graph::BottomLeft:
		DrawX = GetPosition().X;
		break;
	case sunEngine_Graph::Top:
	case sunEngine_Graph::Center:
	case sunEngine_Graph::Bottom:
		DrawX = GetPosition().X - GetSize().X / 2;
		break;
	case sunEngine_Graph::BottomRight:
	case sunEngine_Graph::Right:
	case sunEngine_Graph::TopRight:
		DrawX = GetPosition().X - GetSize().X;
		break;
	default:
		break;
	}
	//glRectf(ViewportX_2_OGL(DrawX), ViewportY_2_OGL(DrawY), ViewportX_2_OGL(DrawX + GetSize().X), ViewportY_2_OGL(DrawY + GetSize().Y));

	glBegin(GL_POLYGON);
	for (int i = 0; i < EdgeCount; i++)
	{
		glVertex2f(ViewportX_2_OGL((GetSize().X / 2.0 / cos(sunEngine::Pi / EdgeCount)) * cos(2 * sunEngine::Pi / EdgeCount * i + GetAngle() * sunEngine::Pi / 180.0 + sunEngine::Pi / EdgeCount) + DrawX + GetSize().X / 2.0),
				   ViewportY_2_OGL((GetSize().X / 2.0 / cos(sunEngine::Pi / EdgeCount)) * sin(2 * sunEngine::Pi / EdgeCount * i + GetAngle() * sunEngine::Pi / 180.0 + sunEngine::Pi / EdgeCount) + DrawY + GetSize().Y / 2.0));
	}
	glDisable(GL_BLEND);
	glEnd();

	//cout<<"Title Rendered"<<endl;
}