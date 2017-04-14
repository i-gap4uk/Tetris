#include "BaseClass.h"
#include "Well.h"
#include "TetraminoController.h"
#include "conio.h"

class Game: public BaseClass
{
private:
	bool _pause;
	bool _gameOver;
	float _gameSpeed;
	bool _dropFigure;
	float time_sum;
	Tetramino _current;
	Tetramino _next;
	Well _well;
	void DrawBorder();
	void DrawWell();
	void DrawNextFigure();
	void DrawCurrentFigure();
	TetraminoController _controller;
	void Restart();
	virtual void UpdateF(float deltatime);
	virtual void KeyPressed(int btn_code);

public :
	Game();
};

Game::Game():BaseClass(50,30),_well(15,20)
{
	_gameSpeed = 0.5;
	_dropFigure = false;
	_gameOver = false;
	_pause = false;
	time_sum = 0;
	
	_controller.ChangeTetramino(_current,_next);
	DrawBorder(); 
	DrawNextFigure();
	DrawWell();
	DrawCurrentFigure();
}

void Game::DrawBorder()
{
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (((i == 0) && (j >= 0 && j <= 21)) ||
				((j == 0 || j == 16) && (i >= 0 && i <= 21)) ||
				(i == 21 && (j >= 0 && j <= 16)) ||
				(i == 5 && (j >= 17 && j <= 21)) ||
				(j == 21 && (i >= 1 && i <= 4)))
				SetChar(j, i, L'#');
		}
	}
}

void Game::DrawWell()
{
	for (int i = 0; i < _well.Height(); i++)
	{
		for (int j = 0; j < _well.Width(); j++)
		{
			if(_well.GetValue(j,i) == false)
				SetChar(j + 1, i + 1, L'.');
			else
				SetChar(j + 1, i + 1, L'*');
		}
	}
};

void Game::DrawNextFigure()
{
	for(int i = 0;i < _next.Size(); i++)
	{
		for(int j = 0;j < _next.Size(); j++)
		{
			if(_next.GetValue(j,i) == true)
				SetChar(17+j,1+i,L'*');
			else
				SetChar(17+j,1+i,L'.');
		}
	}
};

void Game::UpdateF(float deltatime)
{
	if(_gameOver == true)
	{
		_gameOver = false;
		Restart();
		time_sum = 0;
		return;
	}
	if(_pause == true)
		return;

	time_sum += deltatime;

	if(time_sum < _gameSpeed && _dropFigure == false)
		return;

	if(_controller.CanMove(DIRECTION::DOWN, _current,_well) == true)
		_controller.Move(DIRECTION::DOWN, _current,_well);
	else
	{
		_controller.InputFigure(_current,_well);
		_well.DeleteCompletedLines();
		_controller.ChangeTetramino(_current, _next);
		DrawNextFigure();
		_gameSpeed = 0.5;
		_dropFigure = false;
		if(_controller.CanMove(DIRECTION::DOWN, _current, _well) == false)
			_gameOver = true;
	}
	DrawWell();
	DrawCurrentFigure();
	time_sum = 0;
};

void Game::KeyPressed(int btn_code)
{
	if(_dropFigure == true)
		return;

	if(btn_code == 224)
	{
		btn_code = _getch();
		switch(btn_code)
		{
		case 77:// RIGHT
			if(_controller.CanMove(DIRECTION::RIGHT,_current,_well) == true)
				_controller.Move(DIRECTION::RIGHT,_current,_well);
			DrawWell();
	        DrawCurrentFigure();
			break;

		case 75:// LEFT
			if(_controller.CanMove(DIRECTION::LEFT,_current,_well) == true)
				_controller.Move(DIRECTION::LEFT,_current,_well);
			DrawWell();
	        DrawCurrentFigure();
			break;

		case 80:// DROP FIGURE (DOWN)
			_dropFigure = true;
			break;
		}
	}
	else if(btn_code == 32)
	{
		if(_controller.CanRotate(_current,_well) == true)
		{
			_controller.Rotate(_current);
			DrawWell();
	        DrawCurrentFigure();
		}
	}
	else if(btn_code == 27) // EXIT
		exit(0); 
	else if(btn_code == 80 || btn_code == 112) // PAUSE
		_pause = !_pause;
};

void Game::DrawCurrentFigure()
{
	int x = _current.GetPos().X;
	int y = _current.GetPos().Y;

	for(int i = 0;i < _next.Size(); i++)
	{
		for(int j = 0;j < _next.Size(); j++)
		{
			if(_current.GetValue(j,i) == true)
				SetChar(x+j,y+i,L'*');
		}
	}
};

void Game::Restart()
{
	_well.ClearField();
	_controller.ChangeTetramino(_current,_next);
}
