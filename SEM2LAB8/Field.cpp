#include "Field.h"
#include <algorithm>
using namespace std;

Field::Field()
{
	_totalPixelsX = 0;
	_totalPixelsY = 0;
}

Field::Field(int x, int y, int fieldDimension)
{
	_totalPixelsX = x;
	_totalPixelsY = y;

	int width = static_cast<double>(x) / fieldDimension, height = static_cast<double>(y) / fieldDimension;
	_cells.reserve(pow(fieldDimension, 2));

	int idCount = 0;
	for (int cellYNum = 0; cellYNum < fieldDimension; cellYNum++)
	{
		for (int cellXNum = 0; cellXNum < fieldDimension; cellXNum++)
		{
			RECT rectangle;
			SetRect(&rectangle, cellXNum*((double)_totalPixelsX / fieldDimension), cellYNum*((double)_totalPixelsY / fieldDimension),
				(cellXNum + 1)*((double)_totalPixelsX / fieldDimension), (cellYNum + 1)*((double)_totalPixelsY / fieldDimension));
			_cells.push_back(Cell(rectangle, idCount));
			++idCount;
		}
	}
	_marked = vector<bool>(pow(fieldDimension, 2));
}

void Field::prepareBackground(HDC& hdc)
{
	HPEN pen = CreatePen(PS_SOLID, 3, BLACK_PEN);
	HPEN old = (HPEN)SelectObject(hdc, pen);

	for_each(_cells.begin(), _cells.end(), [&hdc, this](const Cell& cell)
	{
		Rectangle(hdc, cell.getRect().left, cell.getRect().top, cell.getRect().right, cell.getRect().bottom);
		if (cell.getMark() == 'o')
			DrawCircle(hdc, cell.getRect());
		if (cell.getMark() == 'x')
			DrawCross(hdc, cell.getRect());
	});

	SelectObject(hdc, old);
	DeleteObject(pen);
}

void Field::putMark(HDC& hdc, int x, int y, char mark)
{
	RECT rect;
	int p1 = (double)x / ((double)_totalPixelsX / sqrt(_cells.size()));
	int p2 = (double)y / ((double)_totalPixelsY / sqrt(_cells.size()));
	int res = getNum(p1, p2);


	HPEN pen = CreatePen(PS_SOLID, 3, BLACK_PEN);
	HPEN old = (HPEN)SelectObject(hdc, pen);

	switch (mark)
	{
	case 'x':
		this->DrawCross(hdc, _cells[res].getRect());
		_cells[res].setMark('x');
		break;
	case 'o':
		this->DrawCircle(hdc, _cells[res].getRect());
		_cells[res].setMark('o');
		break;
	default:
		break;
	}

	SelectObject(hdc, old);
	DeleteObject(pen);
}

char Field::checkWinner() const
{
	bool areX = true, areO = true;
	for (int x = 0; x < sqrt(_cells.size()); x++) // 
	{
		areX = true, areO = true;
		for (int j = 0; j < sqrt(_cells.size()); j++)
		{
			if (_cells[x + j*sqrt(_cells.size())].getMark() == 'x')
				areO = false;
			if (_cells[x + j*sqrt(_cells.size())].getMark() == 'o')
				areX = false;
			if (_cells[x + j*sqrt(_cells.size())].getMark() == '\0')
			{
				areO = false;
				areX = false;
			}
		}
		if (areX) return 'x'; if (areO) return 'o';
	}
	
	areX = true; areO = true;

	for (int y = 0; y < sqrt(_cells.size()); y++) // 
	{
		areX = true, areO = true;
		for (int j = 0; j < sqrt(_cells.size()); j++)
		{
			if (_cells[j + y*sqrt(_cells.size())].getMark() == 'x')
				areO = false;
			if (_cells[j + y*sqrt(_cells.size())].getMark() == 'o')
				areX = false;
			if (_cells[j + y*sqrt(_cells.size())].getMark() == '\0')
			{
				areO = false;
				areX = false;
			}
		}
		if (areX) return 'x'; if (areO) return 'o';
	}

	areX = true; areO = true;

	for (int i =0; i < _cells.size(); i += sqrt(_cells.size()) + 1)
	{
		if (_cells[i].getMark() == 'x')
			areO = false;
		if (_cells[i].getMark() == 'o')
			areX = false;
		if (_cells[i].getMark() == '\0')
		{
			areO = false;
			areX = false;
		}
	}
	if (areX) return 'x'; if (areO) return 'o';

	 // diag 
	areX = true; areO = true;
	for (int i = sqrt(_cells.size()) - 1; i <=  _cells.size() - sqrt(_cells.size()); i += sqrt(_cells.size()) - 1)
	{
		if (_cells[i].getMark() == 'x')
			areO = false;
		if (_cells[i].getMark() == 'o')
			areX = false;
		if (_cells[i].getMark() == '\0')
		{
			areO = false;
			areX = false;
		}
	}
	if (areX) return 'x'; if (areO) return 'o';
	return '\0';
}

void Field::DrawCircle(HDC& hdc, RECT& square)
{
	Ellipse(hdc, square.left, square.top, square.right, square.bottom);
}

void Field::DrawCross(HDC& hdc, RECT& square)
{
	MoveToEx(hdc, square.left, square.top, NULL);
	LineTo(hdc, square.right, square.bottom);
	MoveToEx(hdc, square.left, square.bottom, NULL);
	LineTo(hdc, square.right, square.top);
}

int Field::getNum(int p1, int p2) const
{
	int res = 0;
	for (int i = 0; i < p2; i++)
		res += sqrt(_cells.size());
	res += p1;
	return res;
}