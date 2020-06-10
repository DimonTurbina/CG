#pragma once
#include "PNMClass.h"
#include "NormalV.h"
#include <functional>
#include <algorithm>
#include <utility>

class PrintLine: public PNM
{
public:
	PrintLine();
	void drawLine(int x0, int y0, int x1, int y1, int gamma, double width, const string& fn);
	
private:
	unsigned int gamma;
	void drawPoint(int x, int y);
	void drawPointForWoo(int x, int y, float brightness);
	NormalV makeNormal(int x0, int y0, int x1, int y1, double width);
	void WuDrawLine(float x0, float y0, float x1, float y1, const string& fn);
	vector <pair<int, int>> pointLocations;
	bool flag = true;
};


