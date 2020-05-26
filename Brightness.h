#pragma once
#include "PNMClass.h"
#include "ColorSpaces.h"

enum class Conversions {
	RGBConstValues,
	YCbCrConstValues,
	RGBAuto,
	YCbCrAuto,
	RGBAuto39,
	YCbCrAuto39
};

class Brightness : public ColorSpaces {

public:
	Brightness();
	void setColorSpace(ColorSpace current) { in = current; }
	void AutoBrightness(bool avoid);
	void ChangeBrightness(double difference, double multiple);
	vector<int> GetBrightestDarkest(bool avoid);
private:
};