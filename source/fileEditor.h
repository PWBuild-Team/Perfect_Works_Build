#pragma once
#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include "applyPatch.h"
#include "Resource.h"
#include "partyStatEditor.h"
#include "audioEditor.h"
#include "helper/gameFileTools.h"
#include "helper/fileSystemTools.h"
#include "gameplayFileEditor.h"

class fileEditor
{
	// Global methods
public:
	static void graphicEdits();
	static void gameplayEdits();
	static void scriptEdits();
	static void audioEdits();
	static void modeEdits();
	static void editSLUS(std::string romFile);
	static void makeSLUS(std::string romFile);
	static void exeEdits(std::string file);
	static void editTextSpeed(std::string file);
};

