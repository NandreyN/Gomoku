#pragma once
#include <windef.h>

class Cell
{
public:
	Cell(int ,int,int,int,int);
	Cell(RECT& cellRect,int);
	int getNumber();
	RECT getRect();
private:
	RECT _cellRect;
	int _orderNumber;
};

