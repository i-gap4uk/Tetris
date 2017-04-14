#include "Tetramino.h"
#include "Well.h"

enum DIRECTION
{DOWN = 0, RIGHT, LEFT};

class TetraminoController
{
private:
	void CopyTetramino(Tetramino& source, Tetramino& destination);
	bool _copy[4][4];
	void CreateCopy(Tetramino& t);
public:
	void ChangeTetramino(Tetramino& current, Tetramino& next);
	void InputFigure(Tetramino& t, Well& w);
	bool CanMove(DIRECTION dir, Tetramino& t, Well& w);
	bool CanRotate(Tetramino& t, Well& well);
	void EraseFigure(Tetramino& t, Well& w);
	void Rotate(Tetramino& t);
	void Move(DIRECTION dir, Tetramino& t, Well& w);
};

void TetraminoController::ChangeTetramino(Tetramino& current, Tetramino& next)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			_copy[i][j] = false;
		}
	}
	CopyTetramino(next,current);
	current.GetPos().X = 7;
	current.GetPos().Y = 1;
	next.NewFigure();
}

void TetraminoController::CopyTetramino(Tetramino& source, Tetramino& destination)
{
	for(int i = 0; i < source.Size(); i++)
	{
		for(int j = 0; j < source.Size(); j++)
		{
			destination.SetValue(j,i,source.GetValue(j,i));
		}
	}
	destination.Type() = source.Type();
}

bool TetraminoController::CanMove(DIRECTION dir, Tetramino& t, Well& w)
{
	int x = t.GetPos().X - 1;
	int y = t.GetPos().Y - 1;

	for(int i = 0; i< t.Size();i++)
	{
		for(int j = 0; j< t.Size();j++)
		{
			if(t.GetValue(j,i) == true)
			{
				switch(dir)
				{
				case DIRECTION::DOWN:
					if((y + i) >= (w.Height() - 1))
						return false;
					
					if(w.GetValue(j + x, i + y + 1) == true)
						return false;
					break;

				case DIRECTION::LEFT:
					if(x + j <= 0)  
						return false;

					if(w.GetValue(x + j - 1, y + i) == true)
						return false;
					break;

				case DIRECTION::RIGHT:
					if((x + j)>= (w.Width() - 1))
						return false;

					if(w.GetValue(x + j + 1, y + i) == true)
						return false;
					break;
				}
			}
		}
	}
	return true;
};

void TetraminoController::Move(DIRECTION dir, Tetramino& t, Well& w)
{
	switch(dir)
	{
	case DIRECTION::DOWN:
		t.GetPos().Y++;
		break;

	case DIRECTION::LEFT:
		t.GetPos().X--;
		break;

	case DIRECTION::RIGHT:
		t.GetPos().X++;
		break;
	}
};

void TetraminoController::EraseFigure(Tetramino& t, Well& w)
{
	int x = t.GetPos().X;
	int y = t.GetPos().Y;

	for(int i = 0; i< t.Size();i++)
	{
		for(int j = 0; j< t.Size();j++)
		{
			w.SetValue(x + j, y + i, false);
		}
	}
};

void TetraminoController::InputFigure(Tetramino& t, Well& w)
{
	int x = t.GetPos().X - 1;
	int y = t.GetPos().Y - 1;
	for(int i = 0; i < t.Size();i++)
	{
		for(int j = 0; j < t.Size();j++)
		{
			if(t.GetValue(j,i) == true)
				w.SetValue(x + j,y + i, true);
		}
	}
};

void TetraminoController::Rotate(Tetramino& t)
{
	FIGURE_TYPE type = t.Type();
	if(type == FIGURE_TYPE::O)
		return;
	CreateCopy(t);
	switch(type)
	{
	case FIGURE_TYPE::I:
		for(int i = 0; i < t.Size();i++)
		{
			for(int j = 0; j < t.Size();j++)
			{
				t.SetValue(j,i,_copy[j][i]); 
			}
		}
		return;
		break;
	case FIGURE_TYPE::J:
	case FIGURE_TYPE::L:
	case FIGURE_TYPE::T:
		for(int i = 0; i < t.Size() - 1;i++)
		{
			for(int j = 0; j < t.Size() - 1;j++)
			{
				t.SetValue(j,i,_copy[3 - 1 - j][i]);
			}
		}
		return;
		break;

	case FIGURE_TYPE::Z:
		swap(_copy[0][2],_copy[2][2]);
		swap(_copy[1][0],_copy[1][2]);
		break;

	case FIGURE_TYPE::S:
		swap(_copy[0][0],_copy[2][0]);
		swap(_copy[1][0],_copy[1][2]);
		break;
	}

	for(int i = 0; i < t.Size();i++)
	{
		for(int j = 0; j < t.Size();j++)
		{
			t.SetValue(j,i, _copy[i][j]); 
		}
	}
};

void TetraminoController::CreateCopy(Tetramino& t)
{
	for(int i = 0; i < t.Size();i++)
	{
		for(int j = 0; j < t.Size();j++)
		{
			_copy[i][j] = t.GetValue(j,i);
		}
	}
	
};

bool TetraminoController::CanRotate(Tetramino &t, Well &well)
{
	int x = t.GetPos().X - 1;
	int y = t.GetPos().Y - 1;

	FIGURE_TYPE type = t.Type();
	if(type == FIGURE_TYPE::O)
		return true;

	bool temp [4][4];

	for(int i = 0; i < t.Size();i++)
	{
		for(int j = 0; j < t.Size();j++)
		{
			temp[i][j] = t.GetValue(j,i);
		}
	}

	switch(type)
	{
	case FIGURE_TYPE::I:
		for(int i = 0; i < t.Size();i++)
		{
			for(int j = 0; j < t.Size();j++)
			{
				temp[i][j] = t.GetValue(i,j);
			}
		}
		break;
	case FIGURE_TYPE::J:
	case FIGURE_TYPE::L:
	case FIGURE_TYPE::T:
		for(int i = 0; i < t.Size() - 1;i++)
		{
			for(int j = 0; j < t.Size() - 1;j++)
			{
				temp[i][j] = t.GetValue(i,3 - 1 - j);
			}
		}
		break;

	case FIGURE_TYPE::Z:
		swap(temp[0][2],temp[2][2]);
		swap(temp[1][0],temp[1][2]);
		break;

	case FIGURE_TYPE::S:
		swap(temp[0][0],temp[2][0]);
		swap(temp[1][0],temp[1][2]);
		break;
	}

	for(int i = 0; i < t.Size();i++)
	{
		for(int j = 0; j < t.Size();j++)
		{
			if(temp[i][j] == true)
			{
				if((well.GetValue(x + j, i + y) == true) || 
				  ((x + j) < 0) || 
				  ((x + j) > (well.Width() - 1)))
				return false;
			}
		}
	}
	return true;
}