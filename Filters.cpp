#include "Filters.h"

Filter::Filter(int bits)
{
	this->bits = bits;
	PNM();
}

int Filter::countColorWithBits(int oldPixel) {
	int PixelsBoarderValue = pow(2, bits);
	vector<int> valuesArray(PixelsBoarderValue + 1);
	//cout << valuesArray.size();
	for (int i = 0; i < valuesArray.size(); i++)
	{
		//cout << oldPixel << endl;
		valuesArray[i] = i * 256 / PixelsBoarderValue;
		if (((abs(oldPixel + (256 / PixelsBoarderValue / 2)) >= valuesArray[i]) && (valuesArray[i] >= oldPixel))
			|| ((abs(oldPixel - (256 / PixelsBoarderValue / 2)) <= valuesArray[i]) && (valuesArray[i] <= oldPixel)))
			return valuesArray[i];
	}
	return 0;
}
int Filter::FloydSteinberg(const string& filename)
{

	errorBufferArray.resize(getHeight());
	for (int i = 0; i < getHeight(); ++i)
		errorBufferArray[i].resize(getWidth());

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			/*gspixelsM[i][j] = gspixelsM[i][j] + errorBufferArray[i][j] > 122 ? 255 : 0;
			
			if((j + 1) != getWidth())
				errorBufferArray[i][j + 1] = ((gspixelsM[i][j] + errorBufferArray[i][j] > 127 ? gspixelsM[i][j] - 255 : 255 - gspixelsM[i][j]) /16 * 7);
			if ((i + 1) != getHeight()) {
				if((j - 1) >= 0)
					errorBufferArray[i + 1][j - 1] = ((gspixelsM[i][j] + errorBufferArray[i][j] > 127 ? gspixelsM[i][j] - 255 : 255 - gspixelsM[i][j]) / 16 * 3);
				errorBufferArray[i + 1][j] = ((gspixelsM[i][j] + errorBufferArray[i][j] > 127 ? gspixelsM[i][j] - 255 : 255 - gspixelsM[i][j]) / 16 * 5);
				if((j + 1) != getWidth())
					errorBufferArray[i + 1][j + 1] = ((gspixelsM[i][j] + errorBufferArray[i][j] > 127 ? gspixelsM[i][j] - 255 : 255 - gspixelsM[i][j]) /16);
			}*/

			int oldpixel = gspixelsM[i][j];
			int newpixel = countColorWithBits(oldpixel);
			gspixelsM[i][j] = newpixel;
			int quant_error = oldpixel - newpixel;
			if ((i + 1) != getHeight()) {
				gspixelsM[i + 1][j] = gspixelsM[i + 1][j] + quant_error * 5 / 16;
				if ((j - 1) >= 0)
					gspixelsM[i + 1][j - 1] = gspixelsM[i + 1][j - 1] + quant_error * 3 / 16;
				if ((j + 1) != getWidth())
					gspixelsM[i + 1][j + 1] = gspixelsM[i + 1][j + 1] + quant_error * 1 / 16;
			}
			if ((j + 1) != getWidth())
				gspixelsM[i][j + 1] = gspixelsM[i][j + 1] + quant_error * 7 / 16;
		}
	}

	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}
	return 0;
}

int Filter::JJN(const string& filename)
{
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int oldpixel = gspixelsM[i][j];
			int newpixel = countColorWithBits(oldpixel);
			gspixelsM[i][j] = newpixel;
			int quant_error = oldpixel - newpixel;
			if((i + 2) < getHeight())
			{
				gspixelsM[i + 2][j] = gspixelsM[i + 2][j] + quant_error * 5 / 42;
				if ((j - 1) >= 0)
					gspixelsM[i + 2][j - 1] = gspixelsM[i + 2][j - 1] + quant_error * 3 / 42;
				if ((j + 1) < getWidth())
					gspixelsM[i + 2][j + 1] = gspixelsM[i + 2][j + 1] + quant_error * 3 / 42;
				if ((j - 2) >= 0)
					gspixelsM[i + 2][j - 2] = gspixelsM[i + 2][j - 2] + quant_error * 1 / 42;
				if ((j + 2) < getWidth())
					gspixelsM[i + 2][j + 2] = gspixelsM[i + 2][j + 2] + quant_error * 1 / 42;
			}
			if ((i + 1) < getHeight()) {
				gspixelsM[i + 1][j] = gspixelsM[i + 1][j] + quant_error * 7 / 42;
				if ((j - 1) >= 0)
					gspixelsM[i + 1][j - 1] = gspixelsM[i + 1][j - 1] + quant_error * 5 / 42;
				if ((j + 1) < getWidth())
					gspixelsM[i + 1][j + 1] = gspixelsM[i + 1][j + 1] + quant_error * 5 / 42;
				if ((j - 2) >= 0)
					gspixelsM[i + 1][j - 2] = gspixelsM[i + 1][j - 2] + quant_error * 3 / 42;
				if ((j + 2) < getWidth())
					gspixelsM[i + 1][j + 2] = gspixelsM[i + 1][j + 2] + quant_error * 3 / 42;
			}
			if ((j + 1) < getWidth())
				gspixelsM[i][j + 1] = gspixelsM[i][j + 1] + quant_error * 7 / 42;
			if ((j + 2) < getWidth())
				gspixelsM[i][j + 2] = gspixelsM[i][j + 2] + quant_error * 5 / 42;
			//cout << i << " " << j << endl;
		}
	}

	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}
	return 0;
}

int Filter::Siera(const string& filename)
{
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int oldpixel = gspixelsM[i][j];
			int newpixel = countColorWithBits(oldpixel);
			gspixelsM[i][j] = newpixel;
			int quant_error = oldpixel - newpixel;
			if((i + 2) < getHeight())
			{
				gspixelsM[i + 2][j] = gspixelsM[i + 2][j] + quant_error * 3 / 32;
				if ((j - 1) >= 0)
					gspixelsM[i + 2][j - 1] = gspixelsM[i + 2][j - 1] + quant_error * 2 / 32;
				if ((j + 1) < getWidth())
					gspixelsM[i + 2][j + 1] = gspixelsM[i + 2][j + 1] + quant_error * 2 / 32;
			}
			if ((i + 1) < getHeight()) {
				gspixelsM[i + 1][j] = gspixelsM[i + 1][j] + quant_error * 5 / 42;
				if ((j - 1) >= 0)
					gspixelsM[i + 1][j - 1] = gspixelsM[i + 1][j - 1] + quant_error * 4 / 32;
				if ((j + 1) < getWidth())
					gspixelsM[i + 1][j + 1] = gspixelsM[i + 1][j + 1] + quant_error * 4 / 32;
				if ((j - 2) >= 0)
					gspixelsM[i + 1][j - 2] = gspixelsM[i + 1][j - 2] + quant_error * 2 / 32;
				if ((j + 2) < getWidth())
					gspixelsM[i + 1][j + 2] = gspixelsM[i + 1][j + 2] + quant_error * 2 / 32;
			}
			if ((j + 1) < getWidth())
				gspixelsM[i][j + 1] = gspixelsM[i][j + 1] + quant_error * 5 / 32;
			if ((j + 2) < getWidth())
				gspixelsM[i][j + 2] = gspixelsM[i][j + 2] + quant_error * 3 / 32;
			//cout << i << " " << j << endl;
		}
	}

	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}
	return 0;
}

int Filter::Atkinson(const string& filename)
{
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int oldpixel = gspixelsM[i][j];
			int newpixel = countColorWithBits(oldpixel);
			gspixelsM[i][j] = newpixel;
			int quant_error = oldpixel - newpixel;
			if ((i + 2) < getHeight())
			{
				gspixelsM[i + 2][j] = gspixelsM[i + 2][j] + quant_error / 8;
			}
			if ((i + 1) < getHeight()) {
				gspixelsM[i + 1][j] = gspixelsM[i + 1][j] + quant_error / 8;
				if ((j - 1) >= 0)
					gspixelsM[i + 1][j - 1] = gspixelsM[i + 1][j - 1] + quant_error / 8;
				if ((j + 1) < getWidth())
					gspixelsM[i + 1][j + 1] = gspixelsM[i + 1][j + 1] + quant_error / 8;
			}
			if ((j + 1) < getWidth())
				gspixelsM[i][j + 1] = gspixelsM[i][j + 1] + quant_error / 8;
			if ((j + 2) < getWidth())
				gspixelsM[i][j + 2] = gspixelsM[i][j + 2] + quant_error / 8;
			//cout << i << " " << j << endl;
		}
	}

	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}
	return 0;
}

int Filter::Ordered8x8(const string& filename, int bits)
{
	float mfactor = 255.0/bits;
	float mratio = 1.0 / 17;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int oldpixel = gspixelsM[i][j];
			int quant_error = oldpixel + mfactor * (orderedMatrix[i%8][j%8] - 1/2);
			int newpixel = countColorWithBits(quant_error);
			gspixelsM[i][j] = newpixel;
		}
	}

	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}
	return 0;
}

int Filter::HalfTone4x4(const string& filename, int bits)
{
	float mfactor = 255.0 / bits;
	float mratio = 1.0 / 17;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int oldpixel = gspixelsM[i][j];
			int quant_error = oldpixel + mfactor * (halftoneMatrix[i % 4][j % 4] - 1 / 2);
			int newpixel = countColorWithBits(quant_error);
			gspixelsM[i][j] = newpixel;
		}
	}

	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}
	return 0;
}

int Filter::Random(const string& filename)
{
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int oldpixel = gspixelsM[i][j];
			int quant_error = oldpixel - 64 + rand() % 129 ;
			int newpixel = quant_error > 127 ? 255 : 0;
			gspixelsM[i][j] = newpixel;
		}
	}

	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			pnmPic.put(gspixelsM[i][j]);
		}
	}
	return 0;
}

void Filter::Gradient()
{
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			gspixelsM[i][j] = ((double)j / width) * 255.0;
		}
	}
}
