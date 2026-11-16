#pragma once
#include "pch.h"
#include <string>
#include "fileEditor.h"

class gameplayFileEditor
{
	// Global methods
public:
	static void expRateEdits(std::string file);
	static void removeCap(std::string file);
	static void battleFileEdits();
};

