#pragma once 

class Well
{
private:
	bool** _field;
	short _fieldWidth;
	short _fieldHeight;
	void ClearLine(int index);
	void ShiftLines(int index);
public:
	Well(int x_size ,int y_size);
	void ClearField();
	const short Width()const{ return _fieldWidth;}
	const short Height()const{ return _fieldHeight;}
	const bool GetValue(int x, int y)const;
	void SetValue(int x, int y, bool value);
	void DeleteCompletedLines();
	~Well();
};

Well::Well(int x_size, int y_size)
{
	this->_fieldWidth = x_size;
	this->_fieldHeight = y_size;

	_field = new bool*[_fieldHeight];
	for(int i = 0; i < _fieldHeight;i++)
	{
		_field[i] = new bool[_fieldWidth];
	}
	ClearField();
}

Well::~Well()
{
	for(int i = 0; i < _fieldHeight;i++)
	{
		delete[] _field[i];
	}
	delete[] _field;
}

void Well::ClearField()
{
	for(int i = 0; i < _fieldHeight;i++)
	{
		for(int j = 0; j <_fieldWidth; j++)
		{
			_field[i][j] = false;
		}
	}
}

const bool Well::GetValue(int x, int y)const
{
	return _field[y][x];
}

void Well::SetValue(int x, int y, bool value)
{
	_field[y][x] = value;
}

void Well::ClearLine(int index)
{
	for(int i = 0; i < _fieldWidth; i++)
	{
		_field[index][i] = false;
	}
}

void Well::ShiftLines(int index)
{
	for(int i = index; i > 0; i--)
	{
		for(int j = 0; j <_fieldWidth; j++)
		{
			swap(_field[i][j], _field[i - 1][j]);
		}
	}
}

void Well::DeleteCompletedLines()
{
	int count = 0;
	for(int i = _fieldHeight - 1; i >= 0; i--)
	{
		for(int j = 0; j <_fieldWidth; j++)
		{
			if(_field[i][j] == true)
				count++;
		}
		if(count == _fieldWidth)
		{
			ClearLine(i);
			ShiftLines(i);
			i++;
		}
		count = 0;
	}
}


