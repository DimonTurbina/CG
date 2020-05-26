#include <iostream>
#include "PNMClass.h"
#include "PrintLine.h"
#include "Filters.h"
#include "ColorSpaces.h"
#include "Brightness.h"

enum class PNMTransform {
	Rotate_left,
	Rotate_right,
	Mirror_x,
	Mirror_y,
	Inverse_colors
};

enum class Lab {
	PictureTransform,
	PrintLine,
	Disering,
	ColorSpaces,
	AutoBrightness
};

int main(int argc, char* argv[]) {

	cout << "choose programm: 1 - pic manipulations, 2 - draw line, 3 - я - filters";

	if (argc < 1)
	{
		cout << "not enough commands";
	}
	else
	{
		cout << "choose programm: 1 - pic manipulations, 2 - draw line";
		switch (atoi(argv[1]))
		{
		case(1): {
			PNM check;
			check.open(argv[2]);
			switch (atoi(argv[4]))
			{
			case(static_cast<int>(PNMTransform::Rotate_left)):
				check.inputRotatedLeft(argv[3]);
				break;

			case(static_cast<int>(PNMTransform::Rotate_right)):
				check.inputRotatedRight(argv[3]);
				break;

			case(static_cast<int>(PNMTransform::Mirror_x)):
				check.inputMirrorX(argv[3]);
				break;

			case(static_cast<int>(PNMTransform::Mirror_y)):
				check.inputMirrorY(argv[3]);
				break;

			case(static_cast<int>(PNMTransform::Inverse_colors)):
				check.inputWithInverColors(argv[3]);
				break;
			default:
				cout << "Wrong command";
				break;
			}
		}
			   break;
		case(2): {
			PrintLine Ptest;
			Ptest.open(argv[2]);

			//sorry for magic numbers, i have not got enough time to fix it :(((

			Ptest.drawLine(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), argv[9]);
			
		}
			   break;
		case(3): {
			Filter Ftest(atoi(argv[6]));
			Ftest.open(argv[2]);
			switch (atoi(argv[5]))
			{
			case(1):
				Ftest.FloydSteinberg(argv[3]);
				break;
			case(2):
				Ftest.JJN(argv[3]);
				break;
			case(3):
				Ftest.Siera(argv[3]);
				break;
			case(4):
				Ftest.Atkinson(argv[3]);
				break;
			case(5):
				if (atoi(argv[4]) == 1)
					Ftest.Gradient();
				Ftest.Ordered8x8(argv[3], atoi(argv[6]));
				break;
			case(6):
				if (atoi(argv[4]) == 1)
					Ftest.Gradient();
				Ftest.HalfTone4x4(argv[3], atoi(argv[6]));
				break;
			case(7):
				Ftest.Random(argv[5]);
				break;
			default:
				cout << "Wrong command";
				break;
			}
		}
			break;
		case(4): {
			ColorSpace in;
			ColorSpace out;
			if (strcmp(argv[2],"RGB") == 0)
				in = ColorSpace::RGB;
			if (strcmp(argv[2], "HSL") == 0)
				in = ColorSpace::HSL;
			if (strcmp(argv[2], "HSV") == 0)
				in = ColorSpace::HSV;
			if (strcmp(argv[2], "YCbCr601") == 0)
				in = ColorSpace::YCbCr_601;
			if (strcmp(argv[2], "YCbCr709") == 0)
				in = ColorSpace::YCbCr_709;
			if (strcmp(argv[2], "YCoCg") == 0)
				in = ColorSpace::YCoCg;
			if (strcmp(argv[2], "CMY") == 0)
				in = ColorSpace::CMY;
			if (strcmp(argv[3], "RGB") == 0)
				out = ColorSpace::RGB;
			if (strcmp(argv[3], "HSL") == 0)
				out = ColorSpace::HSL;
			if (strcmp(argv[3], "HSV") == 0)
				out = ColorSpace::HSV;
			if (strcmp(argv[3], "YCbCr601") == 0)
				out = ColorSpace::YCbCr_601;
			if (strcmp(argv[3], "YСbCr709") == 0)
				out = ColorSpace::YCbCr_709;
			if (strcmp(argv[3], "YCoCg") == 0)
				out = ColorSpace::YCoCg;
			if (strcmp(argv[3], "CMY") == 0)
				out = ColorSpace::CMY;
			cout << static_cast<int>(in) << endl;
			cout << static_cast<int>(out) << endl;
			if (atoi(argv[4]) == 1){ 
				ColorSpaces Lab4(in, out);
				Lab4.open(argv[5]);
				Lab4.ConverToRGB();
				Lab4.ConvertFormat();
				Lab4.input(argv[6]);
			}
			if (atoi(argv[4]) == 3) {
				ColorSpaces Lab4(in, out);
				Lab4.OpenMultipleFile(argv[5], argv[6], argv[7]);
				Lab4.ConverToRGB();
				Lab4.ConvertFormat();
				Lab4.SaveMultipleFile(argv[5], argv[6], argv[7]);
			}


		}
			   break;
		case(5): {
			Brightness TestBrightness;
			TestBrightness.open(argv[2]);
			switch (atoi(argv[4]))
			{
			case(static_cast<int>(Conversions::RGBConstValues)):
			{
				cout << "0" << endl;
				TestBrightness.setColorSpace(ColorSpace::RGB);
				double differance = static_cast<double>(atoi(argv[5]));
				double multyply = static_cast<double>(atof(argv[6]));
				TestBrightness.ChangeBrightness(differance, multyply);
				TestBrightness.input(argv[3]);
			}
			break;
			case(static_cast<int>(Conversions::YCbCrConstValues)):
			{
				cout << "1" << endl;
				TestBrightness.setColorSpace(ColorSpace::YCbCr_601);
				double differance = static_cast<double>(atoi(argv[5]));
				double multyply = static_cast<double>(atof(argv[6]));
				TestBrightness.ChangeBrightness(differance, multyply);
				TestBrightness.input(argv[3]);
			}
			break;
			case(static_cast<int>(Conversions::RGBAuto)):
			{
				cout << "2" << endl;
				TestBrightness.setColorSpace(ColorSpace::RGB);
				TestBrightness.AutoBrightness(false);
				TestBrightness.input(argv[3]);
			}
			break;
			case(static_cast<int>(Conversions::YCbCrAuto)):
			{
				cout << "3" << endl;
				TestBrightness.setColorSpace(ColorSpace::YCbCr_601);
				TestBrightness.AutoBrightness(false);
				TestBrightness.input(argv[3]);
			}
			break;
			case(static_cast<int>(Conversions::RGBAuto39)):
			{
				cout << "4" << endl;
				TestBrightness.setColorSpace(ColorSpace::RGB);
				TestBrightness.AutoBrightness(true);
				TestBrightness.input(argv[3]);
			}
			break;
			case(static_cast<int>(Conversions::YCbCrAuto39)):
			{
				cout << "5" << endl;
				TestBrightness.setColorSpace(ColorSpace::YCbCr_601);
				TestBrightness.AutoBrightness(true);
				TestBrightness.input(argv[3]);
			}
			break;
			default:
				break;
			}
		}
		default:
			break;
		}
	}

	/*ColorSpaces testSpace(ColorSpace::YCbCr_709, ColorSpace::RGB);
	testSpace.open("C:\\Users\\dimon\\source\\repos\\CG\\Res\\Check1.pnm");
	testSpace.ConverToRGB();
	testSpace.ConvertFormat();
	testSpace.input("C:\\Users\\dimon\\source\\repos\\CG\\Res\\Check10.pnm");*/
	//PrintLine testLine;

	//testLine.open("C:\\Users\\Dmitrii\\source\\repos\\Project6\\Project6\\imageout.pnm");

	//testLine.drawLine(100, 100, 360, 240, 0, 6, "C:\\Users\\Dmitrii\\source\\repos\\Project6\\Project6\\imageout1.pnm");
	/*PNM c;
	Filter Ftest;
	Ftest.open("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout.pnm");
	Ftest.FloydSteinberg("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout2.pnm");
	Ftest.open("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout.pnm");
	Ftest.JJN("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout3.pnm");
	Ftest.open("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout.pnm");
	Ftest.Siera("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout4.pnm");
	Ftest.open("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout.pnm");
	Ftest.Atkinson("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout5.pnm");
	Ftest.open("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout.pnm");
	Ftest.Ordered8x8("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout6.pnm",6);*/
	//c.open("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout.pnm");
	//c.inputRotatedLeft("C:\\Users\\Марина\\source\\repos\\CG\\CG\\Res\\imageout3.pnm");
}