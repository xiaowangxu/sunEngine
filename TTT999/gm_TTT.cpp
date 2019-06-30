#include "pch.h"
#include "gm_TTT.h"

// ____________________________________________________________
// gm_Postiton
// ____________________________________________________________

gm_TTT_Position::gm_TTT_Position(const int PosX, const int PosY)
{
	if (PosX > 2)		this->X = 2;
	else if (PosX < 0)	this->X = 0;
	else				this->X = PosX;
	if (PosY > 2)		this->Y = 2;
	else if (PosY < 0)	this->Y = 0;
	else				this->Y = PosY;
}

int & gm_TTT_Position::GetX()
{
	return this->X;
}

int & gm_TTT_Position::GetY()
{
	return this->Y;
}

ostream & operator<<(ostream &outstream, const gm_TTT_Position &Pos)
{
	outstream << "(" << Pos.X << "," << Pos.Y << ")";
	return outstream;
}

// ____________________________________________________________
// gm_TTT_Move
// ____________________________________________________________

gm_TTT_Move::gm_TTT_Move(const gm_Player &Mover, const gm_TTT_Position &Pos) :
	Mover(Mover), Position(Pos) {};

ostream & operator<<(ostream &outstream, const gm_TTT_Move &Move)
{
	outstream << "Mover:" << Move.Mover << " Pos:" << Move.Position;
	return outstream;
}

gm_TTT_Position & gm_TTT_Move::GetPos()
{
	return this->Position;
}

gm_Player & gm_TTT_Move::GetMover()
{
	return this->Mover;
}

// ____________________________________________________________
// gm_TTT
// ____________________________________________________________

void gm_TTT::UpdateState()
{
	gm_Player LastChess = Null;
	bool isFull = true;
	// Horizontal
	for (int i = 0; i < 3; i++)
	{
		if (this->Board[i][0] == Null)
		{
			isFull = false;
			continue;
		}
		LastChess = this->Board[i][0];
		for (int j = 1; j < 3; j++)
		{
			if (this->Board[i][j] == Null)
			{
				isFull = false;
				break;
			}
			else if (this->Board[i][j] != LastChess)
			{
				break;
			}
			else
			{
				if (j == 2)
				{
					this->State = Ended;
					this->Winner = LastChess;
					return;
				}
			}
		}
	}
	// Vertical
	for (int j = 0; j < 3; j++)
	{
		if (this->Board[0][j] == Null)
		{
			isFull = false;
			continue;
		}
		LastChess = this->Board[0][j];
		for (int i = 1; i < 3; i++)
		{
			if (this->Board[i][j] == Null)
			{
				isFull = false;
				break;
			}
			else if (this->Board[i][j] != LastChess)
			{
				break;
			}
			else
			{
				if (i == 2)
				{
					this->State = Ended;
					this->Winner = LastChess;
					return;
				}
			}
		}
	}
	// Diagonal
	if (this->Board[0][0] != Null)
	{
		LastChess = this->Board[0][0];
		for (int i = 1; i < 3; i++)
		{
			if (this->Board[i][i] == Null)
			{
				isFull = false;
				break;
			}
			else if (this->Board[i][i] != LastChess)
			{
				break;
			}
			else
			{
				if (i == 2)
				{
					this->State = Ended;
					this->Winner = LastChess;
					return;
				}
			}
		}
	}
	else
	{
		isFull = false;
	}
	if (this->Board[0][2] != Null)
	{
		LastChess = this->Board[0][2];
		for (int i = 1; i < 3; i++)
		{
			if (this->Board[i][2 - i] == Null)
			{
				isFull = false;
				break;
			}
			else if (this->Board[i][2 - i] != LastChess)
			{
				break;
			}
			else
			{
				if (i == 2)
				{
					this->State = Ended;
					this->Winner = LastChess;
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
		this->State = Ended;
		this->Winner = Null;
	}
	else
	{
		this->State = Playing;
		this->Winner = Null;
	}
}

gm_TTT::gm_TTT(int ID) // Construct
{
	this->IID = ID;
	for (int i = 0; i < 3; i++)
	{
		this->ChessWin[i] = gm_TTT_Position();
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->Board[i][j] = Null;

		}
	}
}

bool gm_TTT::Move(gm_TTT_Move Move) // Move Chess
{
	if (this->State == Ended)
	{
		cout << "\n-->> Fail to Move. This match is ended." << endl << endl;
		return false;
	}
	if (this->Board[Move.GetPos().GetX()][Move.GetPos().GetY()] == Null) // Check if the Pos already has chess.
	{
		cout << "\n-->> NOW " << Move << endl << endl;
		this->Board[Move.GetPos().GetX()][Move.GetPos().GetY()] = Move.GetMover();
	}
	else    // Pos is empty.
	{
		cout << "\n-->> Fail to Move. This position already has chess." << endl << endl;
	}
	this->UpdateState();    // Update State after every move.
	return true;
}

void gm_TTT::ForceSet(gm_TTT_Move Move)    // Force a grid to be owned by one mover
{
	this->Board[Move.GetPos().GetX()][Move.GetPos().GetY()] = Move.GetMover();
}

gm_TTT_State gm_TTT::GetState()const  // Get State
{
	return this->State;
}

gm_Player gm_TTT::GetWinner() const // Get Winner
{
	return this->Winner;
}


ostream &operator <<(ostream &outstream, const gm_TTT &TTTBoard)  // Output
{
	outstream << "------------------" << TTTBoard.IID << "------------------\n\n" << "\tState:" << (TTTBoard.State == Playing ? "Playing" : "Ended") << endl << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "\t";
		for (int j = 0; j < 3; j++)
		{
			switch (TTTBoard.Board[i][j])
			{
			case Null:
				outstream << "   ";
				break;
			case Player1:
				outstream << " 1 ";
				break;
			case Player2:
				outstream << " 2 ";
				break;
			default:
				outstream << " E ";
				break;
			}
			if (j < 2) outstream << "|";
		}
		if (i < 2) outstream << endl << "\t-----------" << endl;
	}
	outstream << "\n\n\tResult:" << TTTBoard.Winner << "\n\n-------------------------------------";
	return outstream;
}