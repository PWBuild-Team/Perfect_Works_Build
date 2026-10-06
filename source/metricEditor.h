#pragma once
#include "Window.h"

class metricEditor
{
	// Global methods
public:
	static void decompMenuEdit();
	static void compMenuEdit();
	static void editExe(std::string file);
	static void editStatus(std::string language);
	static void handleReplace(std::string file, std::string language);

	// Global variables
public:
	inline static std::string menuexe = "data\\metrics\\2597.csv";
};

