#pragma once

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

enum gm_TTT_State
{
	Ended,
	Playing
};

enum gm_Player
{
	Null,
	Player1,
	Player2
};

// TTT Board Position Class (X,Y) 0<=X/Y<=2
class gm_TTT_Position
{
private:
	int X, Y;
public:
	gm_TTT_Position(const int PosX = 0, const int PosY = 0);

	int &GetX();
	int &GetY();

	friend ostream &operator<<(ostream &outstream, const gm_TTT_Position &Pos);
};

// TTT Move Class include who move and where to move to
class gm_TTT_Move
{
private:
	gm_Player       Mover = Player1;
	gm_TTT_Position Position;
public:
	gm_TTT_Move(const gm_Player &Mover, const gm_TTT_Position &Pos);

	gm_TTT_Position &GetPos();
	gm_Player &GetMover();

	friend ostream &operator<<(ostream &outstream, const gm_TTT_Move &Move);
};

// TTT Class
class gm_TTT
{
private:
	gm_Player		Board[3][3];
	gm_TTT_State	State = Playing;
	gm_Player		Winner = Null;
	int				IID = 0;
	gm_TTT_Position	ChessWin[3];

	void UpdateState();		// Update the match's state

public:
	gm_TTT(int ID);		// Construct

	bool Move(gm_TTT_Move Move);	// Move Chess

	void ForceSet(gm_TTT_Move Move);	// Force a grid to be owned by one mover
	gm_TTT_State GetState() const;	// Get State
	gm_Player GetWinner() const;	// Get Winner

	friend ostream &operator <<(ostream &outstream, const gm_TTT &TTTBoard);	// Output
};