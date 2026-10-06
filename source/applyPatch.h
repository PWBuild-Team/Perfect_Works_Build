#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Resource.h"
#include "Window.h"
#include "patchProcessor.h"
#include "fileEditor.h"
#include "controlEditor.h"
#include "monsterEditor.h"
#include "graphicalEditor.h"

class fileEditor;

class applyPatch
{
	// Global methods
public:
	static bool patch();
	static void initialise();
	static void prepareFiles();
	static void executeBat();
	static void cleanup();
    static void makeCue();
	static void createTemp();
	static void applyFMV();
	static void backupROM();
	static void iterateTemp();
	

	// Global variables
public:
	inline static std::string fileName;
	inline static std::string cueName;
	inline static std::string cdName;
	inline static std::string oldPath;
	inline static std::string temp = "temp";
	inline static bool patched = false;
	inline static std::ofstream list_file;
	inline static std::ofstream batch_file;
	inline static std::ofstream cue_stream;
};