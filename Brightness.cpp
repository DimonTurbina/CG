#include "Brightness.h"

Brightness::Brightness()
{
}

void Brightness::AutoBrightness(bool avoid)
{
	vector<int> BrightDark;
	BrightDark = GetBrightestDarkest(avoid);
	double difference = BrightDark[1], multiple = 255.0 / (static_cast<double>(BrightDark[0]) - BrightDark[1]);
	std::cout << "Difference: " << difference << endl << "Multiple: " << multiple << endl;
	ChangeBrightness(difference, multiple);
}

void Brightness::ChangeBrightness(double difference, double multiple)
{
	if (pnmformat == "P6") {
		if (in == ColorSpace::RGB)
		{
			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++) 
				{
					int result = (static_cast<double>(pixelsM[i][j].R) - difference) * multiple;
					if (result > 255)
						result = 255;
					if (result < 0)
						result = 0;
					pixelsM[i][j].R = result;
					result = (static_cast<double>(pixelsM[i][j].G) - difference) * multiple;
					if (result > 255)
						result = 255;
					if (result < 0)
						result = 0;
					pixelsM[i][j].G = result;
					result = (static_cast<double>(pixelsM[i][j].B) - difference) * multiple;
					if (result > 255)
						result = 255;
					if (result < 0)
						result = 0;
					pixelsM[i][j].B = result;
				}
			}
		}
		else
		{
			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{
					int result = (static_cast<double>(pixelsM[i][j].R) - difference) * multiple;
					if (result > 255)
						result = 255;
					if (result < 0)
						result = 0;
					pixelsM[i][j].R = result;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				int result = (static_cast<double>(gspixelsM[i][j]) - difference) * multiple;
				if (result > 255)
					result = 255;
				if (result < 0)
					result = 0;
				gspixelsM[i][j] = result;
			}
		}
	}
}

vector<int> Brightness::GetBrightestDarkest(bool avoid)
{
	int ColorsCount[256] = {};
	int brightest;
	int darkest;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			if ((pnmformat == "P6") && (in != ColorSpace::YCbCr_601)) {
				ColorsCount[pixelsM[i][j].R]++;
				ColorsCount[pixelsM[i][j].G]++;
				ColorsCount[pixelsM[i][j].B]++;
			}
			if ((pnmformat == "P6") && (in == ColorSpace::YCbCr_601)) {
				ColorsCount[pixelsM[i][j].R]++;
			}
			if (pnmformat == "P5") {
				ColorsCount[gspixelsM[i][j]]++;
			}
		}
	}

	if (avoid) {
		int numberToDel = 0;
		int deleted = 0;
		int Dposition = 0;
		int Bposition = 255;

		if ((pnmformat == "P6") && (in != ColorSpace::YCbCr_601))
			numberToDel = static_cast<double>(width * height * 3) * 0.0039;
		else
			numberToDel = static_cast<double>(width * height) * 0.0039;
		while (deleted < numberToDel)
		{
			if (deleted % 2 == 0)
			{
				while (ColorsCount[Dposition] == 0)
					Dposition++;
				ColorsCount[Dposition]--;
				deleted++;
			}
			else
			{
				while (ColorsCount[Bposition] == 0)
					Bposition--;
				ColorsCount[Bposition]--;
				deleted++;
			}
		}
	}

	for (int i = 0; i < 256; i++)
	{
		if (ColorsCount[i] > 0)
		{
			darkest = i;
			break;
		}
	}
	for (int i = 255; i >= 0; i--)
	{
		if (ColorsCount[i] > 0)
		{
			brightest = i;
			break;
		}
	}
	return { brightest, darkest };
}
