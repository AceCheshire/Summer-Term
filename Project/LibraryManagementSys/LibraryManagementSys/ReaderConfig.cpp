#include"PageConst.h"
#include"ReaderConst.h"
#include<fstream>
#include<string>
#include<windows.h>

bool Reader::ReadForPointPaint(PageUnitEx* pageUnitListHead, std::string fileName) {
	std::ifstream inputFile;
	inputFile.open(fileName.c_str());
	if (inputFile.is_open()) {
		std::string tmpLine;
		while (getline(inputFile, tmpLine)) {
			short tmpCoordX = (int)tmpLine[X_BASE] * 100 + (int)tmpLine[X_BASE + 1] * 10 + (int)tmpLine[X_BASE + 2] - 48 * 111;
			short tmpCoordY = (int)tmpLine[Y_BASE] * 100 + (int)tmpLine[Y_BASE + 1] * 10 + (int)tmpLine[Y_BASE + 2] - 48 * 111;
			WORD tmpColor = ((((int)tmpLine[COLOR_BASE] * 10 + (int)tmpLine[COLOR_BASE + 1] - 48 * 11) & 0x0F) << 4)
				+ (((int)tmpLine[COLOR_BASE + 2] * 10 + (int)tmpLine[COLOR_BASE + 3] - 48 * 11) & 0x0F);
			COORD tmpCoord = { tmpCoordX,tmpCoordY };
			std::string tmpStr = tmpLine.substr(STR_BASE);
			PageUnit tmpPageUnit = { tmpCoord,tmpColor,tmpStr };
			pageUnitListHead->Append(tmpPageUnit);
		}
		return true;
	}
	else return false;
}