#include <Windows.h>
#include <time.h>

#define SIZE 4

enum FIGURE_TYPE
{I = 0, J, L, O, S, T, Z};

class Tetramino
{
private:
	FIGURE_TYPE _type;
	bool _tetramino[SIZE][SIZE];
	COORD _pos;
	void Clear();
	void EditCoord();
public:
	Tetramino();
	FIGURE_TYPE& Type(){ return _type;}
	COORD& GetPos(){ return _pos;} 
	const int Size()const{ return SIZE;}
	void NewFigure();
	const bool GetValue(unsigned int x, unsigned int y)const
	{
		return _tetramino[y][x];
	}
	void SetValue(unsigned int x, unsigned int y, bool value)
	{
		_tetramino[y][x] = value;
	}
};

Tetramino::Tetramino()
{
	srand(time(0));
	NewFigure();
};

void Tetramino::Clear()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			_tetramino[i][j] = false;
		}
	}
};

void Tetramino::NewFigure()
{
	_type = static_cast<FIGURE_TYPE>(rand() % 7);

	Clear();
	
	switch(_type)
	{
	case FIGURE_TYPE::I:
			for(int i = 0; i < SIZE; i++)
			{
				_tetramino[i][1] = true;
			}
			break;
	case FIGURE_TYPE::J:
			_tetramino[0][1]= true;
			_tetramino[1][1]= true;
			_tetramino[2][1]= true;
			_tetramino[2][0]= true;
			break;
	case FIGURE_TYPE::L:
			_tetramino[0][1]= true;
			_tetramino[1][1]= true;
			_tetramino[2][1]= true;
			_tetramino[2][2]= true;
			break;
	case FIGURE_TYPE::O:
			_tetramino[0][0]= true;
			_tetramino[0][1]= true;
			_tetramino[1][0]= true;
			_tetramino[1][1]= true;
			break;
	case FIGURE_TYPE::S:
			_tetramino[0][0]= true;
			_tetramino[0][1]= true;
			_tetramino[1][1]= true;
			_tetramino[1][2]= true;
			break;
	case FIGURE_TYPE::T:
			_tetramino[0][1]= true;
			_tetramino[1][0]= true;
			_tetramino[1][1]= true;
			_tetramino[1][2]= true;
			break;
	case FIGURE_TYPE::Z:
			_tetramino[0][1]= true;
			_tetramino[0][2]= true;
			_tetramino[1][0]= true;
			_tetramino[1][1]= true;
			break;
	}
	
};

void Tetramino::EditCoord()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(_tetramino[i][j] == true)
			{
				this->_pos.X += j;
				this->_pos.Y += i;
				return;
			}
		}
	}
};
