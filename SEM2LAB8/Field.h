#pragma once
#include <windows.h>
#include <vector>
#include "Cell.h"

class Field
{
public:
	Field();
	Field(int x, int y, int fieldDimension);
	void prepareBackground(HDC& hdc);
	void putMark(HDC &hdc,int x, int y, char mark);
	char checkWinner() const;
private:
	std::vector<Cell> _cells;
	std::vector<bool> _marked;
	int _totalPixelsX, _totalPixelsY;
	void DrawCircle(HDC &hdc, RECT& square);
	void DrawCross(HDC &hdc, RECT& square);
	int getNum(int p1, int p2) const;
};

