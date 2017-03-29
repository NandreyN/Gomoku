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
}

void Field::prepareBackground(HDC& hdc)
{
	HPEN pen = CreatePen(PS_SOLID, 3, BLACK_PEN);
	HPEN old = (HPEN)SelectObject(hdc, pen);

	for_each(_cells.begin(), _cells.end(), [&hdc](const Cell& cell)
	{
		Rectangle(hdc, cell.getRect().left, cell.getRect().top, cell.getRect().right, cell.getRect().bottom);
	});

	SelectObject(hdc, old);
	DeleteObject(pen);
}