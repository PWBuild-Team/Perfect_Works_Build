#pragma once
#include "pch.h"
#include "helper/gameFileTools.h"
#include "helper/fileSystemTools.h"
#include "Window.h"
#include <string>
#include <filesystem>


class controlEditor
{
	// Global methods
public:
	static void addImage(std::string file);
	static void editData(std::string trimfile);
	static void editBattleFile(std::string trimfile);
	static void editExecutable(std::string file);
	static void editBattleExe(std::string file);
	static std::vector<int> popOffset(std::string dataFile);
	static std::vector<int> popValues(std::string dataFile);

	// Global variables
public:
	inline static std::string exediff = "data\\controls\\0022.csv";
	inline static std::string battlediff = "data\\controls\\0038.csv";
};

