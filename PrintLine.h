#pragma once
#include "PNMClass.h"
#include "NormalV.h"

class PrintLine: public PNM
{
public:
	PrintLine();
	void drawLine(int x0, int y0, int x1, int y1, int gamma, double width, const string& fn);
	
private:
	unsigned int gamma;
	void drawPoint(int x, int y);
	NormalV makeNormal(int x0, int y0, int x1, int y1, double width);
	vector <pair<int, int>> pointLocations;
	bool flag = true;
};


