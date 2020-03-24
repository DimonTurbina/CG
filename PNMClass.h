#pragma once
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "RGBStruct.h"

using namespace std;

class PNM
{
public:
	PNM();
	void open(const string&);
	RGB& get(unsigned int, unsigned int);
	unsigned int getWidth();
	unsigned int getHeight();
	string getRange();
	string getFormat();
	void input(const string& filename);
	void inputRotatedLeft(const string& filename);
	void inputRotatedRight(const string& filename);
	void inputMirrorY(const string& filename);
	void inputMirrorX(const string& filename);
	void inputWithInverColors(const string& filename);

protected:
	string filename;
	string range;
	string pnmformat;
	unsigned int width, height;
	vector<RGB> pixels;
	vector<unsigned char> gspixels;
	vector<vector<RGB>> pixelsM;
	vector<vector<unsigned char>> gspixelsM;
};

