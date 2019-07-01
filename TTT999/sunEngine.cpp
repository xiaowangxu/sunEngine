#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;

// config your game setting in "sunEngine_Utility.h"
// to use Mouse Plugin globally
extern MouseObj Mouse;

// Put Your Game Object Here
int Turn=0;

class TicTekToe
{
public:
	Vector2<GLdouble> Position;
	Vector2<GLdouble> Size;
	GLdouble ChessSize;
	Shape Chess[3][3];
	Animater SizeChanger[3][3];
	MouseSensor Touch[3][3];
	int Board[3][3]={0};
public:
	TicTekToe()
	{
		SetBoardPosition(960,540);
		SetBoardSize(500,500);
		SetChessSize(120);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Chess[i][j].AddBehaviour(SizeChanger[i][j]);
				Chess[i][j].AddBehaviour(Touch[i][j]);
				Chess[i][j].SetShape(60,1.0,1.0,1.0);
				Chess[i][j].SetOpacity(0.2);
			}
		}
		
	}

	void SetChessSize(const GLdouble Size)
	{
		ChessSize = Size;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Chess[i][j].SetSize(ChessSize, ChessSize);
			}
		}
	}

	void SetBoardSize(const GLdouble W, const GLdouble H)
	{
		Size = Vector2<GLdouble>(W, H);
		UpdateBoardArrangment();
	}

	void SetBoardPosition(const GLdouble X, const GLdouble Y)
	{
		Position = Vector2<GLdouble>(X, Y);
		UpdateBoardArrangment();
	}

	void UpdateBoardArrangment()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Chess[i][j].SetPosition(Position.X+Size.X / 2.0 *(i-1), Position.Y+Size.Y / 2.0 *(j-1));
			}
		}
	}

	void ChessHighlight(const int i,const int j,bool Highlight)
	{
		if(Highlight)
		{
			SizeChanger[i][j].StopAnimation(bh_Animater::Current);
			SizeChanger[i][j].SetAnimation(Chess[i][j].GetSize().X, 150, 0.3, bh_Animater::BackOut, bh_Animater::Once, bh_Animater::Size);
			SizeChanger[i][j].StartAnimation();
		}
		else
		{
			SizeChanger[i][j].StopAnimation(bh_Animater::Current);
			SizeChanger[i][j].SetAnimation(Chess[i][j].GetSize().X, 120, 0.3, bh_Animater::BackOut, bh_Animater::Once, bh_Animater::Size);
			SizeChanger[i][j].StartAnimation();
		}
	}

	void PutChess(const int i,const int j,const int player)
	{
		if(Board[i][j] == 0)
		{
			Chess[i][j].SetOpacity(1.0);
			Board[i][j]=player;
			SizeChanger[i][j].StopAnimation(bh_Animater::Current);
			SizeChanger[i][j].SetAnimation(120, 150, 0.3, bh_Animater::ElasticOut, bh_Animater::Once, bh_Animater::Size);
			SizeChanger[i][j].StartAnimation();
			if(player == 1)
			{
				Chess[i][j].SetEdgeCount(4);
				Chess[i][j].SetColor(0.96,0.38,0.38);
			}
			else if(player == 2)
			{
				Chess[i][j].SetEdgeCount(6);
				Chess[i][j].SetColor(1.0, 0.94, 0.75);
			}
			Turn++;
		}
		else
		{
			cout<<"Can't Move Here"<<endl;
		}

	}

	void ObjectLoop()
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(Touch[i][j].OnRollIn() && Board[i][j] == 0)
				{
					ChessHighlight(i,j,true);
				}
				if(Touch[i][j].OnRollOut() && Board[i][j] == 0)
				{
					ChessHighlight(i,j,false);
				}
				if(Touch[i][j].OnClick(Mouse_Button::Left))
				{
					if (Turn % 2 == 0)
					{
						PutChess(i,j,1);
					}
					else
					{
						PutChess(i, j, 2);
					}
				}
			}
		}
	}
};

TicTekToe Board1;

void game_Initialize()
{
	// the script here will only run once before the game start
	
}

void game_MainLoop()
{
	// put your main game logic here
	Board1.ObjectLoop();
}