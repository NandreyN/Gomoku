#pragma once
#include <windows.h>

class Cell
{
public:
	Cell(int ,int,int,int,int);
	Cell(RECT& cellRect,int);
	int getNumber() const;
	RECT getRect() const;
	char getMark() const;
	void setMark(char);
private:
	RECT _cellRect;
	int _orderNumber;
	char _mark;
};

