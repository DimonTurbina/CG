#include <iostream>
#include "PNMClass.h"
#include "PrintLine.h"
#include "Filters.h"

enum {
	Rotate_left,
	Rotate_right,
	Mirror_x,
	Mirror_y,
	Inverse_colors
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
			case(1):
				check.inputRotatedLeft(argv[3]);
				break;

			case(2):
				check.inputRotatedRight(argv[3]);
				break;

			case(3):
				check.inputMirrorX(argv[3]);
				break;

			case(4):
				check.inputMirrorY(argv[3]);
				break;

			case(5):
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
			Filter Ftest;
			Ftest.open(argv[2]);
			switch (atoi(argv[4]))
			{
			case(1):
				Ftest.FloydSteinberg(argv[4]);
				break;
			case(2):
				Ftest.JJN(argv[4]);
				break;
			case(3):
				Ftest.Siera(argv[4]);
				break;
			case(4):
				Ftest.Atkinson(argv[4]);
				break;
			case(5):
				if (atoi(argv[3]) == 1)
					Ftest.Gradient();
				Ftest.Ordered8x8(argv[4], atoi(argv[5]));
				break;
			case(6):
				if (atoi(argv[3]) == 1)
					Ftest.Gradient();
				Ftest.HalfTone4x4(argv[4], atoi(argv[5]));
				break;
			case(7):
				Ftest.Random(argv[4]);
				break;
			default:
				cout << "Wrong command";
				break;
			}
		}
		default:
			break;
		}
	}
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