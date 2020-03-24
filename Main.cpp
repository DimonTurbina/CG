#include <iostream>
#include "PNMClass.h"
#include "PrintLine.h"

enum {
	Rotate_left,
	Rotate_right,
	Mirror_x,
	Mirror_y,
	Inverse_colors
};

int main(int argc, char* argv[]) {

	cout << "choose programm: 1 - pic manipulations, 2 - draw line";

	if (argc < 4)
	{
		cout << "not enough commands";
	}
	else
	{
		cout << "choose programm: 1 - pic manipulations, 2 - draw line";
		if (atoi(argv[1]) == 1)
		{
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
		else
		{
			PrintLine test;
			test.open(argv[2]);

			//sorry for magic numbers, i have not got enough time to fix it :(((

			test.drawLine(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), argv[9]);
		}
	}

	//PrintLine testLine;

	//testLine.open("C:\\Users\\Dmitrii\\source\\repos\\Project6\\Project6\\imageout.pnm");

	//testLine.drawLine(100, 100, 360, 240, 0, 6, "C:\\Users\\Dmitrii\\source\\repos\\Project6\\Project6\\imageout1.pnm");


}