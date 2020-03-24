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
		drawLine(v.x0, v.y0, v.x1, v.y1, gamma, 1, fn);

		half = pointLocations.end();

		NormalV v1 = makeNormal(x1, y1, x0, y0, widtgh);
		drawLine(v1.x0, v1.y0, v1.x1, v1.y1, gamma, 1, fn);
		flag = false;

		widtgh = 0;

		vector <pair<int, int>> ::iterator secondHalf = half;

		vector <pair<int, int>> ::iterator firstHalf = pointLocations.begin();

		size_t j = pointLocations.size()/2;
		size_t i = 0;
		while ( i != pointLocations.size()/2)
		{
			drawLine(pointLocations[i].first, pointLocations[i].second, pointLocations[j].first, pointLocations[j].second, gamma, 1, fn);
			drawLine(pointLocations[i].first + 1, pointLocations[i].second, pointLocations[j].first + 1, pointLocations[j].second, gamma, 1, fn);
			i++;
			j++;
			//cout << pointLocations.size() / 2 << " ";
			//cout << i << " ";
		}
		
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
