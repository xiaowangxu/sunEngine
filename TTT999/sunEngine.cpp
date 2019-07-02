#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;

// config your game setting in "sunEngine_Utility.h"
// to use Mouse Plugin globally
extern MouseObj Mouse;

// Put Your Game Object Here
const GLdouble	BlankHighlightSize = 45,
				BlankDehighlingtSize = 20,
				BlankMouseInSize = 55,
				BlankMouseOutSize = 45,
				ChessSize = 70;

const GLfloat	BlankHighlightOpac = 0.15,
				BlankDehighlightOpac = 0.05;

string GameState = "Begin";
enum Player
{
	Player1,Player2
}Turn;
Vector2<int> NextBoard = Vector2<int>(0,0);


class TicTekToe
{
public:
	Vector2<GLdouble> Position;
	Vector2<GLdouble> Size;
	GLdouble BlankSize;
	GLdouble ChessSize = 70;

	Shape Chess[3][3];
	Shape WinnerChess;

	Animater SizeChanger[3][3];
	Animater OpacChanger[3][3];
	Animater WinnerAnimation;
	MouseSensor Touch[3][3];

	int Board[3][3]={0};
	bool isFinished = false;
	int Winner = 0;
	bool Playable = false;

public:
	TicTekToe()
	{
		SetBoardPosition(960,700);
		SetBoardSize(220,220);
		WinnerChess.AddBehaviour(WinnerAnimation);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Chess[i][j].AddBehaviour(SizeChanger[i][j]);
				Chess[i][j].AddBehaviour(OpacChanger[i][j]);
				Chess[i][j].AddBehaviour(Touch[i][j]);
			}
		}
		Reset();
		
	}

	void Reset()
	{
		Playable = false;
		isFinished = false;
		Winner = 0;
		SetChessSize(55);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Board[i][j]=0;
				Chess[i][j].SetShape(60, 1.0, 1.0, 1.0);
				Chess[i][j].SetOpacity(0);
			}
		}
		WinnerChess.SetVisible(sunEngine_Graph::Invisible);
		//cout<<"TTT Reseted"<<endl;
	}

	void TestWinner()
	{
		int LastChess = 0;
		bool isFull = true;
		// Horizontal
		for (int i = 0; i < 3; i++)
		{
			if (Board[i][0] == 0)
			{
				isFull = false;
				continue;
			}
			LastChess = Board[i][0];
			for (int j = 1; j < 3; j++)
			{
				if (Board[i][j] == 0)
				{
					isFull = false;
					break;
				}
				else if (Board[i][j] != LastChess)
				{
					break;
				}
				else
				{
					if (j == 2)
					{
						isFinished = true;
						Winner = LastChess;
						return;
					}
				}
			}
		}
		// Vertical
		for (int j = 0; j < 3; j++)
		{
			if (Board[0][j] == 0)
			{
				isFull = false;
				continue;
			}
			LastChess = Board[0][j];
			for (int i = 1; i < 3; i++)
			{
				if (this->Board[i][j] == 0)
				{
					isFull = false;
					break;
				}
				else if (Board[i][j] != LastChess)
				{
					break;
				}
				else
				{
					if (i == 2)
					{
						isFinished = true;
						Winner = LastChess;
						return;
					}
				}
			}
		}
		// Diagonal
		if (Board[0][0] != 0)
		{
			LastChess = this->Board[0][0];
			for (int i = 1; i < 3; i++)
			{
				if (Board[i][i] == 0)
				{
					isFull = false;
					break;
				}
				else if (Board[i][i] != LastChess)
				{
					break;
				}
				else
				{
					if (i == 2)
					{
						isFinished = true;
						Winner = LastChess;
						return;
					}
				}
			}
		}
		else
		{
			isFull = false;
		}
		if (Board[0][2] != 0)
		{
			LastChess = this->Board[0][2];
			for (int i = 1; i < 3; i++)
			{
				if (Board[i][2 - i] == 0)
				{
					isFull = false;
					break;
				}
				else if (Board[i][2 - i] != LastChess)
				{
					break;
				}
				else
				{
					if (i == 2)
					{
						isFinished = true;
						Winner = LastChess;
						return;
					}
				}
			}
		}
		else
		{
			isFull = false;
		}
		// No One Win
		if (isFull)
		{
			isFinished = true;
			Winner = 0;
		}
		else
		{
			isFinished = false;
			Winner = 0;
		}
	}

	void UpdateWinner()
	{
		if(isFinished)
		{
			if(Winner == 0)
			{

			}
			else if(Winner == 1)
			{
				WinnerChess.SetShape(4, 0.96, 0.38, 0.38);
				WinnerChess.SetVisible(sunEngine_Graph::Visible);
				WinnerAnimation.SetAnimation((Size.X + ChessSize) + 30, Size.X + ChessSize, 0.3, bh_Animater::ElasticOut, bh_Animater::Once, bh_Animater::Size);
				WinnerAnimation.StartAnimation();
				SetBoardVisibility(sunEngine_Graph::Invisible);
			}
			else if(Winner == 2)
			{
				WinnerChess.SetShape(6, 1.0, 0.94, 0.75);
				WinnerChess.SetVisible(sunEngine_Graph::Visible);
				WinnerAnimation.SetAnimation((Size.X + ChessSize) + 30, Size.X + ChessSize, 0.3, bh_Animater::ElasticOut, bh_Animater::Once, bh_Animater::Size);
				WinnerAnimation.StartAnimation();
				SetBoardVisibility(sunEngine_Graph::Invisible);
			}
			else
			{
				WinnerChess.SetVisible(sunEngine_Graph::Invisible);
			}
		}
	}

	void SetChessSize(const GLdouble Size)
	{
		BlankSize = Size;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Chess[i][j].SetSize(BlankSize - 15, BlankSize - 15);
			}
		}
		WinnerChess.SetSize(this->Size.X + ChessSize, this->Size.Y + ChessSize);
	}

	void SetBoardSize(const GLdouble W, const GLdouble H)
	{
		Size = Vector2<GLdouble>(W, H);
		WinnerChess.SetSize(this->Size.X + ChessSize, this->Size.Y + ChessSize);
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
		WinnerChess.SetPosition(Position.X,Position.Y);
	}

	void SetBoardVisibility(const sunEngine_Graph::engine_Graph_Visible visibility)
	{
		switch(visibility)
		{
		case sunEngine_Graph::Visible:
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Chess[i][j].SetVisible(sunEngine_Graph::Visible);
				}
			}
			break;
		case sunEngine_Graph::Invisible:
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Chess[i][j].SetVisible(sunEngine_Graph::Invisible);
				}
			}
			break;
		}
	}

	void BlankHighlight(const int i,const int j,bool Highlight)
	{
		if(Highlight)
		{
			SizeChanger[i][j].StopAnimation(bh_Animater::Current);
			SizeChanger[i][j].SetAnimation(Chess[i][j].GetSize().X, BlankMouseInSize, 0.3, bh_Animater::BackOut, bh_Animater::Once, bh_Animater::Size);
			SizeChanger[i][j].StartAnimation();
		}
		else
		{
			SizeChanger[i][j].StopAnimation(bh_Animater::Current);
			SizeChanger[i][j].SetAnimation(Chess[i][j].GetSize().X, BlankMouseOutSize, 0.3, bh_Animater::BackOut, bh_Animater::Once, bh_Animater::Size);
			SizeChanger[i][j].StartAnimation();
		}
	}

	void MoveChess(const int i,const int j,const int player)
	{
		if(Board[i][j] == 0)
		{
			OpacChanger[i][j].StopAnimation(bh_Animater::Current);
			Chess[i][j].SetOpacity(1.0);
			Board[i][j]=player;
			SizeChanger[i][j].StopAnimation(bh_Animater::Current);
			SizeChanger[i][j].SetAnimation(BlankHighlightSize , ::ChessSize, 0.3, bh_Animater::ElasticOut, bh_Animater::Once, bh_Animater::Size);
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
			NextBoard = Vector2<int>(i,j);
			TestWinner();
			//cout<<"This Board result:"<< (isFinished? "Finished":"Playing")<<endl;
			UpdateWinner();
			GameState = "MoveFinished";
		}
		else
		{
			cout<<"Can't Move Here"<<endl;
		}

	}

	// BoardHighlight
	void BoardHighlight()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(Board[i][j] == 0)		// Nobody Move Here
				{
					SizeChanger[i][j].StopAnimation(bh_Animater::Current);
					SizeChanger[i][j].SetAnimation(Chess[i][j].GetSize().X, BlankHighlightSize, 0.3, bh_Animater::CircleOut, bh_Animater::Once, bh_Animater::Size);
					SizeChanger[i][j].StartAnimation();
					OpacChanger[i][j].StopAnimation(bh_Animater::Current);
					OpacChanger[i][j].SetAnimation(Chess[i][j].GetOpacity(), BlankHighlightOpac, 0.3, bh_Animater::CircleOut, bh_Animater::Once, bh_Animater::Opacity);
					OpacChanger[i][j].StartAnimation();
				}
			}
		}
	}

	void BoardDehighlight()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (Board[i][j] == 0) // Nobody Move Here
				{
					SizeChanger[i][j].StopAnimation(bh_Animater::Current);
					SizeChanger[i][j].SetAnimation(Chess[i][j].GetSize().X, BlankDehighlingtSize, 0.3, bh_Animater::CircleOut, bh_Animater::Once, bh_Animater::Size);
					SizeChanger[i][j].StartAnimation();
					OpacChanger[i][j].StopAnimation(bh_Animater::Current);
					OpacChanger[i][j].SetAnimation(Chess[i][j].GetOpacity(), BlankDehighlightOpac, 0.3, bh_Animater::CircleOut, bh_Animater::Once, bh_Animater::Opacity);
					OpacChanger[i][j].StartAnimation();
				}
			}
		}
	}

	void PlayLoop()
	{
		if(GameState == "Move")
		{
			if(Playable && !isFinished)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (Board[i][j] == 0)	// Has no Chess On this Point
						{
							if (Touch[i][j].OnRollIn())
							{
								BlankHighlight(i,j,1);
							}
							if (Touch[i][j].OnRollOut())
							{
								BlankHighlight(i, j, 0);
							}
							if (Touch[i][j].OnClick(Mouse_Button::Left))
							{
								// Move Chess
								switch (Turn)
								{
								case Player1:
									MoveChess(i,j,1);
									Turn = Player2;
									break;
								case Player2:
									MoveChess(i,j,2);
									Turn = Player1;
									break;
								default:
									break;
								}
							}
						}
					}
				}
			}
		}
	}
};

class TTT999
{
public:
	TicTekToe Board[3][3];

	TTT999()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Board[i][j].SetBoardPosition(960 + 400 * (i - 1), 700 + 400 * (j - 1));
			}
		}
	}

	void Reset()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Board[i][j].Reset();
			}
		}
	}

	void SetPlayable(const int x,const int y)
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Board[i][j].Playable = i==x&&j==y&&!Board[i][j].isFinished ? true:false;
			}
		}
	}

	void SetAllPlayable()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Board[i][j].Playable = Board[i][j].isFinished ? false : true;
			}
		}
	}

	void HighlightPlayable()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(Board[i][j].Playable)
				{
					Board[i][j].BoardHighlight();
					//cout<<"Try to Highlight"<<endl;
				}
				else
				{
					Board[i][j].BoardDehighlight();
					//cout << "Try to Dehighlight" << endl;
				}
			}
		}
	}

	void TTT999Loop()
	{
		if(GameState == "Begin")
		{
			Reset();
			SetAllPlayable();
			HighlightPlayable();
			Turn = Player1;
			GameState = "Move";
			//cout<<"Begin"<<endl;
		}
		if(GameState == "Move")
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Board[i][j].PlayLoop();
				}
			}
		}
		if(GameState == "MoveFinished")
		{
			if(Board[NextBoard.X][NextBoard.Y].isFinished)
			{
				SetAllPlayable();
			}
			else
			{
				SetPlayable(NextBoard.X, NextBoard.Y);
			}
			HighlightPlayable();
			Turn = Turn==Player1? Player1:Player2;
			GameState = "Move";
		}
	}
};

TTT999 GameBoard;

void game_Initialize()
{
	// the script here will only run once before the game start
	
}

void game_MainLoop()
{
	// put your main game logic here
	GameBoard.TTT999Loop();
}