#include "PrintLine.h"

PrintLine::PrintLine()
{
	PNM();
}

void PrintLine::drawLine(int x0, int y0, int x1, int y1, int gamma, double widtgh, const string& fn) 
{

	this->gamma = gamma;

	vector <pair<int, int>> ::iterator half;

	if (widtgh > 1) {
		
		NormalV v = makeNormal(x0, y0, x1, y1, widtgh);
		drawLine(v.x0 - 1, v.y0 - 1, v.x1 - 1, v.y1 - 1, gamma, 1, fn);

		WuDrawLine(v.x0, v.y0, v.x1, v.y1, fn);

		half = pointLocations.end();

		NormalV v1 = makeNormal(x1, y1, x0, y0, widtgh);
		drawLine(v1.x0 + 1, v1.y0 + 1, v1.x1 + 1, v1.y1 + 1, gamma, 1, fn);

		WuDrawLine(v1.x0, v1.y0, v1.x1, v1.y1, fn);

		WuDrawLine(v.x0, v.y0, v1.x0, v1.y0, fn);
		WuDrawLine(v.x1, v.y1, v1.x1, v1.y1, fn);

		flag = false;

		widtgh = 0;

		vector <pair<int, int>> ::iterator secondHalf = half;

		vector <pair<int, int>> ::iterator firstHalf = pointLocations.begin();

		size_t j = pointLocations.size()/2 + 1;
		size_t i = 1;
		while ( i != pointLocations.size()/2 - 1)
		{
			drawLine(pointLocations[i].first, pointLocations[i].second, pointLocations[j].first, pointLocations[j].second, gamma, 1, fn);
			drawLine(pointLocations[i].first + 1, pointLocations[i].second, pointLocations[j].first + 1, pointLocations[j].second, gamma, 1, fn);
			drawLine(pointLocations[i].first - 1, pointLocations[i].second, pointLocations[j].first - 1, pointLocations[j].second, gamma, 1, fn);
			i++;
			j++;
			//cout << pointLocations.size() / 2 << " ";
			//cout << i << " ";
		}
		
		/*if (i == pointLocations.size() / 2) {
			WuDrawLine(v.x0, v.y0, v1.x0, v1.y0, fn);
			WuDrawLine(v.x1, v.y1, v1.x1, v1.y1, fn);
		}*/
	}

	
	int const deltaX = x1 - x0;
	int const deltaY = y1 - y0;

	int const absDeltaX = abs(deltaX);
	int const absDeltaY = abs(deltaY);

	int accreation = 0;

	if (absDeltaX >= absDeltaY) {
		int y = y0;
		const int direction = deltaY != 0 ? (deltaY > 0 ? 1 : -1) : 0;
		for (int x = x0; deltaX > 0 ? x <= x1: x >= x1; deltaX > 0 ? x++ : x--)
		{
			//cout << x << " " << y << endl;
			if (flag == true)
			{
				pointLocations.push_back({x, y});
			}
			drawPoint(x, y);
			
			accreation += absDeltaY;

			if (accreation >= absDeltaX)
			{
				accreation -= absDeltaX;
				y += direction;
			}
		}
	}
	else
	{
		int x = x0;
		const int direction = deltaX != 0 ? (deltaX > 0 ? 1 : -1) : 0;
		for (int y = y0; deltaY > 0 ? y <= y1 : y >= y1; deltaY > 0 ? y++ : y--)
		{
			//cout << x << " " << y << endl;

			if (flag == true)
			{
				pointLocations.push_back({ x, y });
			}

			drawPoint(x, y);
			accreation += absDeltaX;

			if (accreation >= absDeltaY)
			{
				accreation -= absDeltaY;
				x += direction;
			}
		}

	}
	
	ofstream pnmPic(fn, ios::binary);

	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}

	pnmPic.close();
}

void PrintLine::drawPoint(int x, int y)
{
	gspixelsM[y][x] = gamma;
}

void PrintLine::drawPointForWoo(int x, int y, float brightness)
{
	gspixelsM[y][x] = 255 - (255 * brightness);
	cout << brightness << endl;
}

NormalV PrintLine::makeNormal(int x0, int y0, int x1, int y1, double width)
{
	int n = x1 - x0;
	int m = y1 - y0;
	double k = (double)(y0 - y1) / (double)(x0 - x1);
	double b = (double)(-(x1 * y0) + (y1 * x0)) / (double)(x0 - x1);
	double x11 = ((double)y1 + 1.0f / k * (double)x1 - b - width  * sqrt(pow(k, 2) + 1.0f)) * k / (pow(k, 2) + 1.0f);
	double x00 = ((double)y1 + 1.0f / k * (double)x1 - b + width  * sqrt(pow(k, 2) + 1.0f)) * k / (pow(k, 2) + 1.0f);
	double y11 = -1.0f / k * x11 + ((double)y1 + (1.0f / k * (double)x1));
	double y00 = -1.0f / k * x00 + ((double)y1 + (1.0f / k * (double)x1));
	NormalV v;
	v.x0 = (int)floor(x00);
	v.x1 = (int)floor(x11);
	v.y0 = (int)floor(y00);
	v.y1 = (int)floor(y11);
	return v;
}

void PrintLine::WuDrawLine(float x0, float y0, float x1, float y1, const string& fn)
{
	auto ipart = [](float x) -> int {return int(std::floor(x)); };
	auto round = [](float x) -> float {return std::round(x); };
	auto fpart = [](float x) -> float {return x - std::floor(x); };
	auto rfpart = [=](float x) -> float {return 1 - fpart(x); };

	const bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	const float dx = x1 - x0;
	const float dy = y1 - y0;
	const float gradient = (dx == 0) ? 1 : dy / dx;

	int xpx11;
	float intery;
	{
		const float xend = round(x0);
		const float yend = y0 + gradient * (xend - x0);
		const float xgap = rfpart(x0 + 0.5);
		xpx11 = int(xend);
		const int ypx11 = ipart(yend);
		if (steep) {
			drawPointForWoo(ypx11, xpx11, rfpart(yend) * xgap);
			drawPointForWoo(ypx11 + 1, xpx11, fpart(yend) * xgap);
		}
		else {
			drawPointForWoo(xpx11, ypx11, rfpart(yend) * xgap);
			drawPointForWoo(xpx11, ypx11 + 1, fpart(yend) * xgap);
		}
		intery = yend + gradient;
	}

	int xpx12;
	{
		const float xend = round(x1);
		const float yend = y1 + gradient * (xend - x1);
		const float xgap = rfpart(x1 + 0.5);
		xpx12 = int(xend);
		const int ypx12 = ipart(yend);
		if (steep) {
			drawPointForWoo(ypx12, xpx12, rfpart(yend) * xgap);
			drawPointForWoo(ypx12 + 1, xpx12, fpart(yend) * xgap);
		}
		else {
			drawPointForWoo(xpx12, ypx12, rfpart(yend) * xgap);
			drawPointForWoo(xpx12, ypx12 + 1, fpart(yend) * xgap);
		}
	}

	if (steep) {
		for (int x = xpx11 + 1; x < xpx12; x++) {
			drawPointForWoo(ipart(intery), x, rfpart(intery));
			drawPointForWoo(ipart(intery) + 1, x, fpart(intery));
			intery += gradient;
		}
	}
	else {
		for (int x = xpx11 + 1; x < xpx12; x++) {
			drawPointForWoo(x, ipart(intery), rfpart(intery));
			drawPointForWoo(x, ipart(intery) + 1, fpart(intery));
			intery += gradient;
		}
	}

	ofstream pnmPic(fn, ios::binary);

	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}

	pnmPic.close();
}
