#include "Cell.h"
#include <winuser.h>

Cell::Cell(int left, int top, int right, int bottom, int number) 
{
	SetRect(&_cellRect,left,top, right, bottom);
}

Cell::Cell(RECT& cellRect, int number)
{
	_cellRect = cellRect;
}

int Cell::getNumber()
{
	return _orderNumber;
}

RECT Cell::getRect()
{
	return _cellRect;
}