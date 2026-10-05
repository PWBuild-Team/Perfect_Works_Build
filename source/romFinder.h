#pragma once
#include "Window.h"
#include <shellapi.h>
#include <commdlg.h>
#include <iostream>
#include <filesystem>
#include <fstream> 
#include <sstream>
#include <string>
#include <bitset>


class romFinder
{
	// Global methods
public:
	static void browseFiles();
	static void searchCD(std::string path);
	static void setPathText(std::string path, int num);
	static void romErrorMsg();
	static void findDiscNum(std::string path);
	static bool getFound();
	static int getDisc();

	// Private variables
private:
	std::string name;

	// Global variables
public:
	inline static OPENFILENAMEA ofn;
	inline static bool xenoFound = false;
	inline static bool discFound1 = false;
	inline static bool discFound2 = false;
	inline static int discNum = 0;
	inline static int fileSize = 0;
	// Some dumps omit the 2-second (150 sector) postgap at the end of the disc
	inline static const int postgapBytes = 150 * 2352;
	inline static bool padDisc1 = false;
	inline static bool padDisc2 = false;
	inline static unsigned char buffer;
};

