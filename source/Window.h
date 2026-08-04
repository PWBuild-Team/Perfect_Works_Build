#pragma once
#include "pch.h"
#include <vector>
#include <string>
#include <iostream>
#include "windowHandler.h"
#include "toolGenerator.h"
#include "Resource.h"
#include "romFinder.h"
#include "patchProcessor.h"
#include "windowPainter.h"

struct tipDesc {
	char text_encounters[255] =
		"Lowers encounter rate for all areas except\n"
		"for the end of disc dungeons, key grinding\n"
		"spots and places where you'd be dependent\n"
		"on encounter drops.";
	char text_fast[255] =
		"Allows a faster text scroll. There are noticeable\n"
		"bugs with specific scenes, so the patch is\n"
		"still a work in progress\n";
	char text_exp[255] =
		"Increases experience from battle. Choose\n"
		"the modifier in the menu below.\n";
	char text_gold[255] =
		"Increases gold from battle. Choose\n"
		"the modifier in the menu below.\n";
	char text_itemspells[255] =
		"WARNING: Incompatible with pre-0.4 saves.\n"
		"The game is rebalanced; with items,\n" 
		"characters and the damage formula receiving\n"
		"adjustment. Other significant overhauls are\n"
		"included. Several features need fine tuning,\n"
		"meaning some bugs are to be expected.";
	char text_monsters[255] =
		"Enemies and bosses will be altered to give\n"
		"a bigger challenge. Recommended for second\n"
		"playthroughs.";
	char text_script[255] =
		"Retranslates names, locations, and keywords to\n"
		"better align with the Japanese version and\n"
		"relocalizes the script to have fewer\n"
		"grammatical errors, confusing lines, and\n"
		"less awkward phrasing in important scenes.\n"
		"This process may take a while.";
	char text_barena[255] =
		"Only the essentials of the rebalance\n"
		"for casual play and fighting the CPU.";
	char text_earena[255] =
		"Additional tweaks tailored to \n"
		"improve the PVP experience in 2P mode.\n";
	char text_resize[255] =
		"Fixes bugs with portraits and corrects\n"
		"proportions when running the game at its\n" 
		"native aspect ratio (approx 3:2, letterboxed\n"
		"within a 10:7 display aspect ratio). Avoid if\n" 
		"your emulator stretches the aspect ratio\n" 
		"to 4:3, or you're using a texture hack.\n";
	char text_fmvs[255] =
		"Changes the FMVs so that they use\n"
		"the Japanese audio and subtitles\n"
		"which are closer to the original\n"
		"script.";
	char text_portraits[255] =
		"Fixes graphical bugs with\n"
		"portraits while keeping them at their\n"
		"original proportions. If you are using\n"
		"a texture hack, you may NOT\n"
		"need this fix. These fixes are\n"
		"also available with resized portraits.\n";
	char text_voices[255] =
		"Switches to the Japanese voices\n"
		"used in battle and the Speed\n"
		"minigame.";
	char text_narena[255] =
		"Uses the Battle Arena balancing\n"
		"from the base game.\n";
	char text_story_mode[255] =
		"Turns off random encounters entirely\n"
		"and ensures all enemies in the game\n"
		"can be killed in one hit.\n";
	char text_flashes[255] =
		"Turns off flashes during battle.";
	char text_roni[255] =
		"Swaps Roni's portrait for his\n"
		"Perfect Works design.\n";
	char text_cafe[255] =
		"Emeralda now uses a sitting\n"
		"sprite over her nanoreactor\n"
		"one when eating at the Aveh\n"
		"cafe.\n";
	char text_deathblow[255] =
		"Removes level requirements from\n"
		"Deathblows. While button combos\n"
		"are still required to learn\n"
		"Deathblows, the player can learn\n"
		"any of them when the game begins\n"
		"Other rebalance patches were not\n"
		"designed around this, so expect it\n"
		"to make the game easier.";
	char text_jpn_control[255] =
		"Switch to the Japanese control\n"
		"scheme. This applies to the\n"
		"overworld, battles, and the\n"
		"speed minigame.";
	char text_music[255] =
		"Adjusts the music placement in\n"
		"specific scenes so that they are\n"
		"are more appropriate and prevents\n"
		"some tracks from being overplayed.";
	char text_expList[255] =
		"Select which value enemy experience\n"
		"should be multiplied by.\n";
	char text_goldList[255] =
		"Select which value enemy gold\n"
		"should be multiplied by.\n";
	char text_instantText[255] =
		"Allows instant text. As with the original\n"
		"patch by FFMaster, there are bugs with\n"
		"specific scenes if the player mashes too\n"
		"quickly.\n";
	char text_cap[255] =
		"Turns off the 9999 damage cap. Works for\n"
		"both character and Gear battles. The\n"
		"rebalance patches have not been adjusted\n"
		"around it, so expect it to make the game\n"
		"easier.";
	char text_bug_fix[255] =
		"Ignores all other patches and just implements\n"
		"the bug fixes.\n";
};

class Window
{
	// Global mathods
public:
	Window(HWND hWnd, HINSTANCE hInst, int axisX, int axisY, LPWSTR szTitle);
	~Window();
	static void checkboxLock();
	static void restoreDefaults();
	static void patchBoxLock();
	void initialise();
	void paintProcess();
	void tooltipTextMaker();
	void openFile(HWND hWnd);
	static void windowSelect();
	void process();
	void dropdown(NMBCDROPDOWN* pDropDown, std::string option);

	// Global variables
public:
	HWND browsebutton1;
	HWND browsebutton2;
	HWND aboutbutton;
	inline static HWND patchbutton;
	inline static HWND cd1path;
	inline static HWND cd2path;
	inline static HWND winHwnd;
	inline static HWND resize;
	inline static HWND portraits;
	inline static HWND flashes;
	inline static HWND roni;
	inline static HWND cafe;
	inline static HWND encounters;
	inline static HWND experience;
	inline static HWND expList;
	inline static HWND gold;
	inline static HWND goldList;
	inline static HWND itemspells;
	inline static HWND monsters;
	inline static HWND deathblows;
	inline static HWND normalarena;
	inline static HWND basicarena;
	inline static HWND expertarena;
	inline static HWND fasttext;
	inline static HWND script;
	inline static HWND fmvs;
	inline static HWND voice;
	inline static HWND storyMode;
	inline static HWND jpnControls;
	inline static HWND music;
	inline static HWND instant;
	inline static HWND cap;
	inline static HWND bugFix;
	inline static HINSTANCE winInst;
	inline static int winX;
	inline static int winY;
	inline static int discNum;
	inline static float graphicsx = 0.03;
	inline static float gameplayx = 0.18;
	inline static float arenax = 0.36;
	inline static float storyx = 0.51;
	inline static float audiox = 0.69;
	inline static float smx = 0.84;
	inline static std::vector<HWND> windList;
	inline static std::vector<HWND> gameplayWindList;
	inline static std::vector<HWND> pathList;
	inline static std::vector<HWND> buttonList;
	inline static bool pathFound1 = false;
	inline static bool pathFound2 = false;
	inline static bool found = false;
	inline static bool checkfound = false;
	inline static std::ofstream log_file;
	inline static std::string path1 = "";
	inline static std::string path2 = "";
	inline static std::string home = std::filesystem::current_path().string();
	inline static std::string expModifier = "";
	inline static std::string goldModifier = "";
	inline static LPWSTR title;
	inline static NMBCDROPDOWN* dropDown;
};

