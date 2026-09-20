#pragma once
#include "Window.h"

class metricEditor
{
	// Global methods
public:
	static void process();
	static void decompMenuEdit();
	static void compMenuEdit();
	static void editExe(std::string file);

	// Global variables
public:
	inline static std::string menuexe = "data\\metrics\\2597.csv";
};

