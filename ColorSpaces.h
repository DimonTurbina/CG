#pragma once
#include "PNMClass.h"

enum class ColorSpace {
	RGB,
	HSL,
	HSV,
	YCbCr_601,
	YCbCr_709,
	YCoCg,
	CMY
};

class ColorSpaces : public PNM {
public:
	ColorSpaces();
	ColorSpaces(ColorSpace in, ColorSpace out);
	void ConvertFormat();
	void ConverToRGB();
	void OpenMultipleFile(string f1, string f2, string f3);
	void SaveMultipleFile(string f1, string f2, string f3);
	string filenameArrey[3];
protected:
	string colorFormatInput;
	string colorFormatOutput;
	ColorSpace in;
	ColorSpace out;
	int convert;
	vector<vector<RGB>> multapleMatrix;
};