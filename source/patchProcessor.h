#pragma once
#include "pch.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "Resource.h"
#include "patchVerifier.h"
#include "applyPatch.h"

class Window;

class patchProcessor
{
	// Global methods
public:
	static void prepare(int discNum, std::string path);
	static void removeWhitespace();
	static void start();
	static void initialisePatchLists();
	static void finish();
	static void reinitialisePatches();
	static void clearPatchLists();
	static bool gamefileVerify();
	static bool oneDriveCheck();

	// Global variables
public:
	inline static bool space = false;
	inline static bool filePathValid = false;
	inline static bool successMessage = false;
	inline static bool editExe = false;
	inline static int num;
	inline static std::string tempPath;
	inline static std::string filePath;
	inline static std::string encountersName = "";
	inline static std::string expName = "";
	inline static std::string fastName = "";
	inline static std::string fmvName = "";
	inline static std::string roniName = "";
	inline static std::string itemspellsName = "";
	inline static std::string monsterName = "";
	inline static std::string resizeName = "";
	inline static std::string scriptName = "";
	inline static std::string arenaName = "";
	inline static std::string portraitsName = "";
	inline static std::string bugName = "";
	inline static std::string titleName = "";
	inline static std::string voiceName = "";
	inline static std::string flashesName = "";
	inline static std::string storyModeName = "";
	inline static std::string goldName = "";
	inline static std::string fmvPatch = "";
	inline static std::string cafeName = "";
	inline static std::string exeName1 = "executable\\cd1";
	inline static std::string exeName2 = "executable\\cd2";
	inline static std::string deathblowName = "";
	inline static std::string jpnName = "";
	inline static std::string musicName = "";
	inline static std::string slusDisc1 = "sub_executable\\disc1";
	inline static std::string slusDisc2 = "sub_executable\\disc2";
	inline static std::string gamefilePath = "gamefiles";
	inline static std::vector<std::string> patchList;
	inline static std::string metricsName = "";
};

