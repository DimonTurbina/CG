#include "PNMClass.h"

PNM::PNM()
{
	width = 0;
	height = 0;
}

void PNM::open(const string& path) {
	ifstream fp(path.c_str(), ios::binary);
	if (fp.fail())
	{
		cout << "some problems";
		return;
	}

	string mg_num, width_str, height_str, range_str;
	fp >> mg_num;
	if (mg_num != "P6" && mg_num != "P5") {
		fp.close();
		cout << "non allowed format";
		return;
	}

	filename = path;
	pnmformat = mg_num;


	fp >> width_str >> height_str >> range_str;

	range = range_str;

	cout << endl << width_str << endl;
	char* ptr;
	width = stoi(width_str);
	ptr = NULL;

	height = stoi(height_str);

	ptr = NULL;

	pixels.clear();
	gspixels.clear();
	if (pnmformat == "P6")
	{
		RGB tmp;

		unsigned char r, g, b;
		fp.seekg(1, std::ios::cur);

		for (unsigned int i = 0; i < width * height; i++) {

			fp.read((char*)&r, sizeof(tmp.R));
			tmp.R = r;

			fp.read((char*)&g, sizeof(tmp.G));
			tmp.G = g;

			fp.read((char*)&b, sizeof(tmp.B));
			tmp.B = b;

			pixels.push_back(tmp);
		}

		pixelsM.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			pixelsM[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				pixelsM[i][j] = pixels[n];
			}
		}

		fp.close();
	}
	else
	{
		unsigned char gs;
		fp.seekg(1, std::ios::cur);
		for (unsigned int i = 0; i < width * height; i++) {

			fp.read((char*)&gs, sizeof(unsigned char));

			gspixels.push_back(gs);
		}

		gspixelsM.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			gspixelsM[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				gspixelsM[i][j] = gspixels[n];
			}
		}

		fp.close();
	}
}

RGB& PNM::get(unsigned int a, unsigned int b) {
	return pixels[(b * width) + a];
}

string PNM::getFormat() {
	return pnmformat;
}

unsigned int PNM::getWidth() {
	return width;
}

unsigned int PNM::getHeight() {
	return height;
}

string PNM::getRange()
{
	return range;
}

void PNM::input(const string& filename) {
	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;
	if (getFormat() == "P6")
	{
		for (int i = 0; i < getHeight() * getWidth(); i++)
		{
			pnmPic.put(pixels[i].R);
			pnmPic.put(pixels[i].G);
			pnmPic.put(pixels[i].B);
		}

		pnmPic.close();
	}
	else
	{
		for (int i = 0; i < getHeight() * getWidth(); i++)
		{
			pnmPic.put(gspixels[i]);
		}
		pnmPic.close();
	}
}

void PNM::inputWithInverColors(const string& filename) {
	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;
	if (getFormat() == "P6")
	{
		for (int i = 0; i < getHeight() * getWidth(); i++)
		{
			pnmPic.put(stoi(getRange()) - pixels[i].R);
			pnmPic.put(stoi(getRange()) - pixels[i].G);
			pnmPic.put(stoi(getRange()) - pixels[i].B);
		}
	}
	else
	{
		for (int i = 0; i < getHeight() * getWidth(); i++)
		{
			pnmPic.put(stoi(getRange()) - gspixels[i]);
		}
	}
	pnmPic.close();
}

void PNM::inputRotatedLeft(const string& filename) {
	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getHeight() << " " <<getWidth() << endl << getRange() << endl;
	if (getFormat() == "P6")
	{

		vector<vector<RGB>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = pixels[n];
			}
		}

		vector<vector<RGB>> transMat;
		transMat.resize(getWidth());
		for (int i = 0; i < getWidth(); ++i)
			transMat[i].resize(getHeight());

		for (int i = 0, n = getWidth() - 1; i <getWidth(); i++, n--)
		{
			for (int j = 0; j < getHeight(); j++)
			{
				transMat[i][j].R = dataMat[j][n].R;
				transMat[i][j].G = dataMat[j][n].G;
				transMat[i][j].B = dataMat[j][n].B;
			}
		}

		for (int i = 0; i < getWidth(); i++)
		{
			for (int j = 0; j < getHeight(); j++)
			{
				pnmPic.put(transMat[i][j].R);
				pnmPic.put(transMat[i][j].G);
				pnmPic.put(transMat[i][j].B);
			}
		}
	}
	else
	{
		vector<vector<unsigned char>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = gspixels[n];
			}
		}

		vector<vector<unsigned char>> transMat;
		transMat.resize(getWidth());
		for (int i = 0; i < getWidth(); ++i)
			transMat[i].resize(getHeight());

		for (int i = 0, n = getWidth() - 1; i < getWidth(); i++, n--)
		{
			for (int j = 0; j < getHeight(); j++)
			{
				transMat[i][j] = dataMat[j][n];
			}
		}

		for (int i = 0; i < getWidth(); i++)
		{
			for (int j = 0; j < getHeight(); j++)
			{
				pnmPic.put(transMat[i][j]);
			}
		}
	}
	pnmPic.close();
}

void PNM::inputRotatedRight(const string& filename) {
	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getHeight() << " " << getWidth() << endl << getRange() << endl;

	if (getFormat() == "P6")
	{
		vector<vector<RGB>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = pixels[n];
			}
		}

		vector<vector<RGB>> transMat;
		transMat.resize(getWidth());
		for (int i = 0; i < getWidth(); ++i)
			transMat[i].resize(getHeight());

		for (int i = 0; i < getWidth(); i++)
		{
			for (int j = 0, n = getHeight() - 1; j < getHeight(); j++, n--)
			{
				transMat[i][j].R = dataMat[n][i].R;
				transMat[i][j].G = dataMat[n][i].G;
				transMat[i][j].B = dataMat[n][i].B;
			}
		}

		for (int i = 0; i < getWidth(); i++)
		{
			for (int j = 0; j < getHeight(); j++)
			{
				pnmPic.put(transMat[i][j].R);
				pnmPic.put(transMat[i][j].G);
				pnmPic.put(transMat[i][j].B);
			}
		}
	}
	else
	{
		vector<vector<unsigned char>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = gspixels[n];
			}
		}

		vector<vector<unsigned char>> transMat;
		transMat.resize(getWidth());
		for (int i = 0; i < getWidth(); ++i)
			transMat[i].resize(getHeight());

		for (int i = 0; i < getWidth(); i++)
		{
			for (int j = 0, n = getHeight() - 1; j < getHeight(); j++, n--)
			{
				transMat[i][j] = dataMat[n][i];
			}
		}

		for (int i = 0; i < getWidth(); i++)
		{
			for (int j = 0; j < getHeight(); j++)
			{
				pnmPic.put(transMat[i][j]);
			}
		}
	}
	pnmPic.close();
}

void PNM::inputMirrorY(const string& filename)
{
	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	if (getFormat() == "P6")
	{
		vector<vector<RGB>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = pixels[n];
			}
		}
		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				pnmPic.put(dataMat[i][getWidth() - 1 - j].R);
				pnmPic.put(dataMat[i][getWidth() - 1 - j].G);
				pnmPic.put(dataMat[i][getWidth() - 1 - j].B);
			}
		}
	}
	else
	{
		vector<vector<unsigned char>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = gspixels[n];
			}
		}
		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				pnmPic.put(dataMat[i][getWidth() - 1 - j]);
			}
		}
	}
	pnmPic.close();
}

void PNM::inputMirrorX(const string& filename)
{
	ofstream pnmPic(filename, ios::binary);
	pnmPic << getFormat() << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

	if (getFormat() == "P6")
	{
		vector<vector<RGB>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = pixels[n];
			}
		}
		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				pnmPic.put(dataMat[getHeight() - 1 - i][j].R);
				pnmPic.put(dataMat[getHeight() - 1 - i][j].G);
				pnmPic.put(dataMat[getHeight() - 1 - i][j].B);
			}
		}
	}
	else
	{
		vector<vector<unsigned char>> dataMat;

		dataMat.resize(getHeight());
		for (int i = 0; i < getHeight(); ++i)
			dataMat[i].resize(getWidth());

		for (int i = 0, n = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++, n++)
			{
				dataMat[i][j] = gspixels[n];
			}
		}
		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				pnmPic.put(dataMat[getHeight() - 1 - i][j]);
			}
		}
	}
	pnmPic.close();
}