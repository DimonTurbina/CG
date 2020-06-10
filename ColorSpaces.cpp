#include "ColorSpaces.h"
#include <algorithm>

ColorSpaces::ColorSpaces()
{
}

ColorSpaces::ColorSpaces(ColorSpace in, ColorSpace out)
{
	PNM();
	this->in = in;
	this->out = out;
}

void ColorSpaces::ConvertFormat()
{
	if (in == out)
		return;

	if (pnmformat == "P6") {
		if (in != out) {
			switch (out)
			{
			case(ColorSpace::RGB):
				return;
			case(ColorSpace::HSL):
				{
					double H, S;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double R = pixelsM[i][j].R / 255.0;
							double G = pixelsM[i][j].G / 255.0;
							double B = pixelsM[i][j].B / 255.0;
							double Max = max(R, max(G, B));
							double Min = min(R, min(G, B));
							double V = Max;
							double C = Max - Min;
							double L = V - C / 2.0;
							if (C == 0)
								H = 0;
							else
							{
								if (V == R)
									H = (60.0) * ((G - B) / C);
								else if (V == G)
									H = (60.0) * (2 + (B - R) / C);
								else if (V == B)
									H = (60.0) * (4 + (R - G) / C);
								else
									H = 0;
							}
							S = ((L == 0) || (L == 1)) ? 0 : ((V - L) / min(L, 1 - L));
							pixelsM[i][j].B = L * 255.0;
							pixelsM[i][j].G = static_cast<int>(S * 255.0);
							pixelsM[i][j].R = static_cast<int>((H / 360.0) * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::HSV):
				{
					double H, S;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double R = pixelsM[i][j].R / 255.0;
							double G = pixelsM[i][j].G / 255.0;
							double B = pixelsM[i][j].B / 255.0;
							double Max = max(R, max(G, B));
							double Min = min(R, min(G, B));
							double V = Max;
							double C = Max - Min;
							double L = V - C / 2.0;
							if (C == 0)
								H = 0;
							else
							{
								if (V == R)
									H = (60.0) * ((G - B) / C);
								else if (V == G)
									H = (60.0) * (2 + (B - R) / C);
								else if (V == B)
									H = (60.0) * (4 + (R - G) / C);
								else
									H = 0;
							}
							S = (V == 0) ? 0 : C / V;
							pixelsM[i][j].B = static_cast<int>(V * 255.0);
							pixelsM[i][j].G = static_cast<int>(S * 255.0);
							pixelsM[i][j].R = static_cast<int>((H / 360.0) * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::YCbCr_601):
				{
					double Kr = 0.299;
					double Kg = 0.587;
					double Kb = 0.114;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double R = pixelsM[i][j].R / 255.0;
							double G = pixelsM[i][j].G / 255.0;
							double B = pixelsM[i][j].B / 255.0;
							double Y = Kr * R + Kg * G + Kb * B;
							double Cb = 0.5 * ((B - Y) / (1.0 - Kb));
							double Cr = 0.5 * ((R - Y) / (1.0 - Kr));
							pixelsM[i][j].R = static_cast<int>(Y * 255.0);
							pixelsM[i][j].G = static_cast<int>((Cb + 0.5) * 255.0);
							pixelsM[i][j].B = static_cast<int>((Cr + 0.5) * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::YCbCr_709):
				{
					double Kr = 0.0722;
					double Kg = 0.2126;
					double Kb = 0.7152;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double R = pixelsM[i][j].R / 255.0;
							double G = pixelsM[i][j].G / 255.0;
							double B = pixelsM[i][j].B / 255.0;
							double Y = Kr * R + Kg * G + Kb * B;
							double Cb = 0.5 * ((B - Y) / (1.0 - Kb));
							double Cr = 0.5 * ((R - Y) / (1.0 - Kr));
							pixelsM[i][j].R = static_cast<int>(Y * 255.0);
							pixelsM[i][j].G = static_cast<int>((Cb + 0.5) * 255.0);
							pixelsM[i][j].B = static_cast<int>((Cr + 0.5) * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::YCoCg):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double R = pixelsM[i][j].R / 255.0;
							double G = pixelsM[i][j].G / 255.0;
							double B = pixelsM[i][j].B / 255.0;
							double Y = R / 4 + G / 2 + B / 4;
							double Co = R / 2 - B / 2;
							double Cg = -R / 4 + G / 2 - B / 4;
							pixelsM[i][j].R = static_cast<int>(Y * 255.0);
							pixelsM[i][j].G = static_cast<int>((Co + 0.5) * 255.0);
							pixelsM[i][j].B = static_cast<int>((Cg + 0.5) * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::CMY):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double R = pixelsM[i][j].R / 255.0;
							double G = pixelsM[i][j].G / 255.0;
							double B = pixelsM[i][j].B / 255.0;
							double C = 1 - R;
							double M = 1 - G;
							double Y = 1 - B;
							pixelsM[i][j].R = static_cast<int>(C * 255.0);
							pixelsM[i][j].G = static_cast<int>(M * 255.0);
							pixelsM[i][j].B = static_cast<int>(Y * 255.0);
						}
					}
					break;
				}
			default:
				break;
			}
		}
	}

	if (pnmformat == "P5") {
		switch (out)
		{
		case(ColorSpace::RGB):
			return;
		case(ColorSpace::HSL):
			{
				double H, S;
				for (int i = 0; i < getHeight(); i++)
				{
					for (int j = 0; j < getWidth(); j++)
					{
						double R = multapleMatrix[i][j].R / 255.0;
						double G = multapleMatrix[i][j].G / 255.0;
						double B = multapleMatrix[i][j].B / 255.0;
						double Max = max(R, max(G, B));
						double Min = min(R, min(G, B));
						double V = Max;
						double C = Max - Min;
						double L = V - C / 2.0;
						if (C == 0)
							H = 0;
						else
						{
							if (V == R)
								H = (60.0) * ((G - B) / C);
							else if (V == G)
								H = (60.0) * (2 + (B - R) / C);
							else if (V == B)
								H = (60.0) * (4 + (R - G) / C);
							else
								H = 0;
						}
						S = ((L == 0) || (L == 1)) ? 0 : ((V - L) / min(L, 1 - L));
						multapleMatrix[i][j].B = L * 255.0;
						multapleMatrix[i][j].G = static_cast<int>(S * 255.0);
						multapleMatrix[i][j].R = static_cast<int>((H / 360.0) * 255.0);
					}
				}
				break;
			}
		case(ColorSpace::HSV):
			{
				double H, S;
				for (int i = 0; i < getHeight(); i++)
				{
					for (int j = 0; j < getWidth(); j++)
					{
						double R = multapleMatrix[i][j].R / 255.0;
						double G = multapleMatrix[i][j].G / 255.0;
						double B = multapleMatrix[i][j].B / 255.0;
						double Max = max(R, max(G, B));
						double Min = min(R, min(G, B));
						double V = Max;
						double C = Max - Min;
						double L = V - C / 2.0;
						if (C == 0)
							H = 0;
						else
						{
							if (V == R)
								H = (60.0) * ((G - B) / C);
							else if (V == G)
								H = (60.0) * (2 + (B - R) / C);
							else if (V == B)
								H = (60.0) * (4 + (R - G) / C);
							else
								H = 0;
						}
						S = (V == 0) ? 0 : C / V;
						multapleMatrix[i][j].B = static_cast<int>(V * 255.0);
						multapleMatrix[i][j].G = static_cast<int>(S * 255.0);
						multapleMatrix[i][j].R = static_cast<int>((H / 360.0) * 255.0);
					}
				}
				break;
			}
		case(ColorSpace::YCbCr_601):
			{
				double Kr = 0.299;
				double Kg = 0.587;
				double Kb = 0.114;
				for (int i = 0; i < getHeight(); i++)
				{
					for (int j = 0; j < getWidth(); j++)
					{
						double R = multapleMatrix[i][j].R / 255.0;
						double G = multapleMatrix[i][j].G / 255.0;
						double B = multapleMatrix[i][j].B / 255.0;
						double Y = Kr * R + Kg * G + Kb * B;
						double Cb = 0.5 * ((B - Y) / (1.0 - Kb));
						double Cr = 0.5 * ((R - Y) / (1.0 - Kr));
						multapleMatrix[i][j].R = static_cast<int>(Y * 255.0);
						multapleMatrix[i][j].G = static_cast<int>((Cb + 0.5) * 255.0);
						multapleMatrix[i][j].B = static_cast<int>((Cr + 0.5) * 255.0);
					}
				}
				break;
			}
		case(ColorSpace::YCbCr_709):
			{
				double Kr = 0.0722;
				double Kg = 0.2126;
				double Kb = 0.7152;
				for (int i = 0; i < getHeight(); i++)
				{
					for (int j = 0; j < getWidth(); j++)
					{
						double R = multapleMatrix[i][j].R / 255.0;
						double G = multapleMatrix[i][j].G / 255.0;
						double B = multapleMatrix[i][j].B / 255.0;
						double Y = Kr * R + Kg * G + Kb * B;
						double Cb = 0.5 * ((B - Y) / (1.0 - Kb));
						double Cr = 0.5 * ((R - Y) / (1.0 - Kr));
						multapleMatrix[i][j].R = static_cast<int>(Y * 255.0);
						multapleMatrix[i][j].G = static_cast<int>((Cb + 0.5) * 255.0);
						multapleMatrix[i][j].B = static_cast<int>((Cr + 0.5) * 255.0);
					}
				}
				break;
			}
		case(ColorSpace::YCoCg):
			{
				for (int i = 0; i < getHeight(); i++)
				{
					for (int j = 0; j < getWidth(); j++)
					{
						double R = multapleMatrix[i][j].R / 255.0;
						double G = multapleMatrix[i][j].G / 255.0;
						double B = multapleMatrix[i][j].B / 255.0;
						double Y = R / 4 + G / 2 + B / 4;
						double Co = R / 2 - B / 2;
						double Cg = -R / 4 + G / 2 - B / 4;
						multapleMatrix[i][j].R = static_cast<int>(Y * 255.0);
						multapleMatrix[i][j].G = static_cast<int>((Co + 0.5) * 255.0);
						multapleMatrix[i][j].B = static_cast<int>((Cg + 0.5) * 255.0);
					}
				}
				break;
			}
		case(ColorSpace::CMY):
			{
				for (int i = 0; i < getHeight(); i++)
				{
					for (int j = 0; j < getWidth(); j++)
					{
						double R = multapleMatrix[i][j].R / 255.0;
						double G = multapleMatrix[i][j].G / 255.0;
						double B = multapleMatrix[i][j].B / 255.0;
						double C = 1 - R;
						double M = 1 - G;
						double Y = 1 - B;
						multapleMatrix[i][j].R = static_cast<int>(C * 255.0);
						multapleMatrix[i][j].G = static_cast<int>(M * 255.0);
						multapleMatrix[i][j].B = static_cast<int>(Y * 255.0);
					}
				}
				break;
			}
		default:
			break;
		}
	}
}

void ColorSpaces::ConverToRGB()
{
	if (in == ColorSpace::RGB)
		return;

	if (pnmformat == "P6") {
		if (in == ColorSpace::RGB)
			return;
		if (in != out)
			switch (in)
			{
			case(ColorSpace::HSL):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double H = static_cast<double>(pixelsM[i][j].R) / 255 * 360;
							double S = static_cast<double>(pixelsM[i][j].G) / 255;
							double L = static_cast<double>(pixelsM[i][j].B) / 255;
							double C = (1 - abs(2 * L - 1)) * S;
							double X = C * ((1 - abs(fmod(H / 60, 2) - 1)));
							double m = L - C / 2;
							double dR;
							double dG;
							double dB;
							if (pixelsM[i][j].R < 60 * 255 / 360) {
								dR = C;
								dG = X;
								dB = 0.0f;
							}
							if ((pixelsM[i][j].R >= 60 * 255 / 360) && (pixelsM[i][j].R < 120 * 255 / 360)) {
								dR = X;
								dG = C;
								dB = 0.0f;
							}
							if ((pixelsM[i][j].R >= 120 * 255 / 360) && (pixelsM[i][j].R < 180 * 255 / 360)) {
								dR = 0;
								dG = C;
								dB = X;
							}
							if ((pixelsM[i][j].R >= 180 * 255 / 360) && (pixelsM[i][j].R < 240 * 255 / 360)) {
								dR = 0.0f;
								dG = X;
								dB = C;
							}
							if ((pixelsM[i][j].R >= 240 * 255 / 360) && (pixelsM[i][j].R < 300 * 255 / 360)) {
								dR = X;
								dG = 0.0f;
								dB = C;
							}
							if ((pixelsM[i][j].R >= 300 * 255 / 360) && (pixelsM[i][j].R < 360 * 255 / 360)) {
								dR = C;
								dG = 0.0f;
								dB = X;
							}
							pixelsM[i][j].R = static_cast<int>((dR + m) * 255);
							pixelsM[i][j].G = static_cast<int>((dG + m) * 255);
							pixelsM[i][j].B = static_cast<int>((dB + m) * 255);
						}
					}
					break;
				}
			case(ColorSpace::HSV):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double H = static_cast<double>(pixelsM[i][j].R) / 255 * 360;
							double S = static_cast<double>(pixelsM[i][j].G) / 255;
							double V = static_cast<double>(pixelsM[i][j].B) / 255;
							double C = S * V;
							double X = C * (1 - abs(fmod(H / 60, 2) - 1));
							double m = V - C;
							double dR;
							double dG;
							double dB;
							if (pixelsM[i][j].R < 60 * 255 / 360) {
								dR = C;
								dG = X;
								dB = 0;
							}
							if ((pixelsM[i][j].R >= 60 * 255 / 360) && (pixelsM[i][j].R < 120 * 255 / 360)) {
								dR = X;
								dG = C;
								dB = 0;
							}
							if ((pixelsM[i][j].R >= 120 * 255 / 360) && (pixelsM[i][j].R < 180 * 255 / 360)) {
								dR = 0;
								dG = C;
								dB = X;
							}
							if ((pixelsM[i][j].R >= 180 * 255 / 360) && (pixelsM[i][j].R < 240 * 255 / 360)) {
								dR = 0;
								dG = X;
								dB = C;
							}
							if ((pixelsM[i][j].R >= 240 * 255 / 360) && (pixelsM[i][j].R < 300 * 255 / 360)) {
								dR = X;
								dG = 0;
								dB = C;
							}
							if ((pixelsM[i][j].R >= 300 * 255 / 360) && (pixelsM[i][j].R < 360 * 255 / 360)) {
								dR = C;
								dG = 0;
								dB = X;
							}
							pixelsM[i][j].R = static_cast<int>((dR + m) * 255);
							pixelsM[i][j].G = static_cast<int>((dG + m) * 255);
							pixelsM[i][j].B = static_cast<int>((dB + m) * 255);
						}
					}
					break;
				}
			case(ColorSpace::YCbCr_601):
				{
					double Kr = 0.299;
					double Kg = 0.587;
					double Kb = 0.114;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double Y = pixelsM[i][j].R / 255.0;
							double Cb = (pixelsM[i][j].G / 255.0) - 0.5;
							double Cr = (pixelsM[i][j].B / 255.0) - 0.5;
							double R = (Y + Cr * (2.0 - 2.0 * Kr));
							double G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
							double B = (Y + (2.0 - 2.0 * Kb) * Cb);
							if (R < 0)
								R = 0;
							if (G < 0)
								G = 0;
							if (B < 0)
								B = 0;
							if (R > 1)
								R = 1;
							if (G > 1)
								G = 1;
							if (B > 1)
								B = 1;
							pixelsM[i][j].R = static_cast<int>(R * 255);
							pixelsM[i][j].G = static_cast<int>(G * 255);
							pixelsM[i][j].B = static_cast<int>(B * 255);
						}
					}
					break;
				}
			case(ColorSpace::YCbCr_709):
				{
					double Kr = 0.0722;
					double Kg = 0.2126;
					double Kb = 0.7152;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double Y = pixelsM[i][j].R / 255.0;
							double Cb = (pixelsM[i][j].G / 255.0) - 0.5;
							double Cr = (pixelsM[i][j].B / 255.0) - 0.5;
							double R = (Y + Cr * (2.0 - 2.0 * Kr));
							double G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
							double B = (Y + (2.0 - 2.0 * Kb) * Cb);
							if (R < 0)
								R = 0;
							if (G < 0)
								G = 0;
							if (B < 0)
								B = 0;
							if (R > 1)
								R = 1;
							if (G > 1)
								G = 1;
							if (B > 1)
								B = 1;
							pixelsM[i][j].R = static_cast<int>(R * 255);
							pixelsM[i][j].G = static_cast<int>(G * 255);
							pixelsM[i][j].B = static_cast<int>(B * 255);
						}
					}
					break;
				}
			case(ColorSpace::YCoCg):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double Y = pixelsM[i][j].R / 255.0;
							double Co = (pixelsM[i][j].G / 255.0) - 0.5;
							double Cg = (pixelsM[i][j].B / 255.0) - 0.5;
							double R = Y + Co - Cg;
							double G = Y + Cg;
							double B = Y - Co - Cg;
							if (R < 0)
								R = 0;
							if (G < 0)
								G = 0;
							if (B < 0)
								B = 0;
							if (R > 1)
								R = 1;
							if (G > 1)
								G = 1;
							if (B > 1)
								B = 1;
							pixelsM[i][j].R = static_cast <int>(R * 255.0);
							pixelsM[i][j].G = static_cast <int>(G * 255.0);
							pixelsM[i][j].B = static_cast <int>(B * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::CMY):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double C = static_cast<double>(pixelsM[i][j].R / 255);
							double M = static_cast<double>(pixelsM[i][j].G / 255);
							double Y = static_cast<double>(pixelsM[i][j].B / 255);
							pixelsM[i][j].R = static_cast <int>(255 * (1 - C));
							pixelsM[i][j].G = static_cast <int>(255 * (1 - M));
							pixelsM[i][j].B = static_cast <int>(255 * (1 - Y));
						}
					}
				}
			default:
				break;
			}
	}

	if (pnmformat == "P5") {
		if (in == ColorSpace::RGB)
			return;
		if (in != out)
			switch (out)
			{
			case(ColorSpace::HSL):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double H = static_cast<double>(multapleMatrix[i][j].R) / 255 * 360;
							double S = static_cast<double>(multapleMatrix[i][j].G) / 255;
							double L = static_cast<double>(multapleMatrix[i][j].B) / 255;
							double C = (1 - abs(2 * L - 1)) * S;
							double X = C * ((1 - abs(fmod(H / 60, 2) - 1)));
							double m = L - C / 2;
							double dR;
							double dG;
							double dB;
							if (multapleMatrix[i][j].R < 60 * 255 / 360) {
								dR = C;
								dG = X;
								dB = 0;
							}
							if ((multapleMatrix[i][j].R >= 60 * 255 / 360) && (multapleMatrix[i][j].R < 120 * 255 / 360)) {
								dR = X;
								dG = C;
								dB = 0;
							}
							if ((multapleMatrix[i][j].R >= 120 * 255 / 360) && (multapleMatrix[i][j].R < 180 * 255 / 360)) {
								dR = 0;
								dG = C;
								dB = X;
							}
							if ((multapleMatrix[i][j].R >= 180 * 255 / 360) && (multapleMatrix[i][j].R < 240 * 255 / 360)) {
								dR = 0;
								dG = X;
								dB = C;
							}
							if ((multapleMatrix[i][j].R >= 240 * 255 / 360) && (multapleMatrix[i][j].R < 300 * 255 / 360)) {
								dR = X;
								dG = 0;
								dB = C;
							}
							if ((multapleMatrix[i][j].R >= 300 * 255 / 360) && (multapleMatrix[i][j].R < 360 * 255 / 360)) {
								dR = C;
								dG = 0;
								dB = X;
							}
							multapleMatrix[i][j].R = static_cast<int>((dR + m) * 255);
							multapleMatrix[i][j].G = static_cast<int>((dG + m) * 255);
							multapleMatrix[i][j].B = static_cast<int>((dB + m) * 255);
						}
					}
					break;
				}
			case(ColorSpace::HSV):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							//double S = static_cast<double>(pixelsM[i][j].G) * 255 / 100;
							//double V = static_cast<double>(pixelsM[i][j].B) * 255 / 100;
							double H = static_cast<double>(multapleMatrix[i][j].R) / 255 * 360;
							double S = static_cast<double>(multapleMatrix[i][j].G) / 255;
							double V = static_cast<double>(multapleMatrix[i][j].B) / 255;
							double C = S * V;
							double X = C * (1 - abs(fmod(H / 60, 2) - 1));
							double m = V - C;
							double dR;
							double dG;
							double dB;
							if (multapleMatrix[i][j].R < 60 * 255 / 360) {
								dR = C;
								dG = X;
								dB = 0;
							}
							if ((multapleMatrix[i][j].R >= 60 * 255 / 360) && (multapleMatrix[i][j].R < 120 * 255 / 360)) {
								dR = X;
								dG = C;
								dB = 0;
							}
							if ((multapleMatrix[i][j].R >= 120 * 255 / 360) && (multapleMatrix[i][j].R < 180 * 255 / 360)) {
								dR = 0;
								dG = C;
								dB = X;
							}
							if ((multapleMatrix[i][j].R >= 180 * 255 / 360) && (multapleMatrix[i][j].R < 240 * 255 / 360)) {
								dR = 0;
								dG = X;
								dB = C;
							}
							if ((multapleMatrix[i][j].R >= 240 * 255 / 360) && (multapleMatrix[i][j].R < 300 * 255 / 360)) {
								dR = X;
								dG = 0;
								dB = C;
							}
							if ((multapleMatrix[i][j].R >= 300 * 255 / 360) && (multapleMatrix[i][j].R < 360 * 255 / 360)) {
								dR = C;
								dG = 0;
								dB = X;
							}
							multapleMatrix[i][j].R = static_cast<int>((dR + m) * 255);
							multapleMatrix[i][j].G = static_cast<int>((dG + m) * 255);
							multapleMatrix[i][j].B = static_cast<int>((dB + m) * 255);
						}
					}
					break;
				}
			case(ColorSpace::YCbCr_601):
				{
					double Kr = 0.299;
					double Kg = 0.587;
					double Kb = 0.114;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double Y = multapleMatrix[i][j].R / 255.0;
							double Cb = (multapleMatrix[i][j].G / 255.0) - 0.5;
							double Cr = (multapleMatrix[i][j].B / 255.0) - 0.5;
							double R = (Y + Cr * (2.0 - 2.0 * Kr));
							double G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
							double B = (Y + (2.0 - 2.0 * Kb) * Cb);
							if (R < 0)
								R = 0;
							if (G < 0)
								G = 0;
							if (B < 0)
								B = 0;
							if (R > 1)
								R = 1;
							if (G > 1)
								G = 1;
							if (B > 1)
								B = 1;
							multapleMatrix[i][j].R = static_cast<int>(R * 255.0);
							multapleMatrix[i][j].G = static_cast<int>(G * 255.0);
							multapleMatrix[i][j].B = static_cast<int>(B * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::YCbCr_709):
				{
					double Kr = 0.0722;
					double Kg = 0.2126;
					double Kb = 0.7152;
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double Y = multapleMatrix[i][j].R / 255.0;
							double Cb = (multapleMatrix[i][j].G / 255.0) - 0.5;
							double Cr = (multapleMatrix[i][j].B / 255.0) - 0.5;
							double R = (Y + Cr * (2.0 - 2.0 * Kr));
							double G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
							double B = (Y + (2.0 - 2.0 * Kb) * Cb);
							if (R < 0)
								R = 0;
							if (G < 0)
								G = 0;
							if (B < 0)
								B = 0;
							if (R > 1)
								R = 1;
							if (G > 1)
								G = 1;
							if (B > 1)
								B = 1;
							multapleMatrix[i][j].R = static_cast<int>(R * 255.0);
							multapleMatrix[i][j].G = static_cast<int>(G * 255.0);
							multapleMatrix[i][j].B = static_cast<int>(B * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::YCoCg):
				{
					for (int i = 0; i < getHeight(); i++)
					{
						for (int j = 0; j < getWidth(); j++)
						{
							double Y = multapleMatrix[i][j].R / 255.0;
							double Co = (multapleMatrix[i][j].G / 255.0) - 0.5;
							double Cg = (multapleMatrix[i][j].B / 255.0) - 0.5;
							double R = Y + Co - Cg;
							double G = Y + Cg;
							double B = Y - Co - Cg;
							if (R < 0)
								R = 0;
							if (G < 0)
								G = 0;
							if (B < 0)
								B = 0;
							if (R > 1)
								R = 1;
							if (G > 1)
								G = 1;
							if (B > 1)
								B = 1;
							multapleMatrix[i][j].R = static_cast <int>(R * 255.0);
							multapleMatrix[i][j].G = static_cast <int>(G * 255.0);
							multapleMatrix[i][j].B = static_cast <int>(B * 255.0);
						}
					}
					break;
				}
			case(ColorSpace::CMY):
				{
				for (int i = 0; i < getHeight(); i++)
				{
					for (int j = 0; j < getWidth(); j++)
					{
						double C = static_cast<double>(multapleMatrix[i][j].R / 255);
						double M = static_cast<double>(multapleMatrix[i][j].G / 255);
						double Y = static_cast<double>(multapleMatrix[i][j].B / 255);
						multapleMatrix[i][j].R = static_cast <int>(255 * (1 - C));
						multapleMatrix[i][j].G = static_cast <int>(255 * (1 - M));
						multapleMatrix[i][j].B = static_cast <int>(255 * (1 - Y));
					}
				}
				break;
				}
			default:
				break;
			}
	}
}

void ColorSpaces::OpenMultipleFile(string f1, string f2, string f3)
{
	open(f1);
	multapleMatrix.resize(getHeight());
	for (size_t i = 0; i < getHeight(); i++) {
		multapleMatrix[i].resize(getWidth());
	}
	for (int k = 0; k < getWidth(); k++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			multapleMatrix[k][j].R = gspixelsM[k][j];
		}
	}

	open(f2);
	for (int k = 0; k < getWidth(); k++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			multapleMatrix[k][j].G = gspixelsM[k][j];
		}
	}

	open(f3);
	for (int k = 0; k < getWidth(); k++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			multapleMatrix[k][j].B = gspixelsM[k][j];
		}
	}
}

void ColorSpaces::SaveMultipleFile(string f1, string f2, string f3)
{
	filenameArrey[0] = f1;
	filenameArrey[1] = f2;
	filenameArrey[2] = f3;
	for (int k = 0; k < 3; k++)
	{
		if (k == 0) {
			ofstream pnmPic(filenameArrey[k], ios::binary);
			pnmPic << "P5" << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{
					pnmPic.put(pixelsM[i][j].R);
				}
			}
		}
		if (k == 1) {
			ofstream pnmPic(filenameArrey[k], ios::binary);
			pnmPic << "P5" << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{
					pnmPic.put(pixelsM[i][j].G);
				}
			}
		}
		if (k == 2) {
			ofstream pnmPic(filenameArrey[k], ios::binary);
			pnmPic << "P5" << endl << getWidth() << " " << getHeight() << endl << getRange() << endl;

			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{
					pnmPic.put(pixelsM[i][j].B);
				}
			}
		}

	}
}

