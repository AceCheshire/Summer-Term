#include<fstream>
#include<iostream>
#include<string>
#include"ReaderConst.h"
#include"PageConst.h"

bool Reader::ReadForPointPaint(PageUnitEx* pageUnitListHead, std::string fileName) {
	std::ifstream inputFile;
	inputFile.open(fileName.c_str());
	if (inputFile.is_open()) {
		std::string tmpLine;
		while (getline(inputFile, tmpLine)) {
			pageUnitListHead.
		}
	}
}