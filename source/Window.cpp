#include "pch.h"
#include "Window.h"

Window::Window(HWND hWnd, HINSTANCE hInst, int axisX, int axisY, LPWSTR szTitle) {
	// Initialise variables
	winHwnd = hWnd;
	winInst = hInst;
	winX = axisX;
	winY = axisY;
	title = szTitle;
	std::filesystem::current_path(home);
	// Create log
	log_file.open("pw_log.txt", std::ios::trunc);
	prepareLog();
	// Create window
	log_file << "Creating windows." << std::endl;
	initialise();
}

Window::~Window() {
}

void Window::initialise() {
	// Create windows for ROM paths
	cd1path = CreateWindow(L"EDIT", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, (int)(winX * 0.15), (int)(winY * 0.03), 500, 25, winHwnd, NULL, winInst, NULL);
	cd2path = CreateWindow(L"EDIT", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, (int)(winX * 0.15), (int)(winY * 0.09), 500, 25, winHwnd, NULL, winInst, NULL);
	// Put in window list
	pathList.emplace_back(cd1path);
	pathList.emplace_back(cd2path);
	// Create buttons
	browsebutton1 = CreateWindow(L"BUTTON", L"Browse", WS_CHILD | WS_VISIBLE, (int)(winX * 0.85), (int)(winY * 0.03), 70, 25, winHwnd, (HMENU)9001, winInst, NULL);
	browsebutton2 = CreateWindow(L"BUTTON", L"Browse", WS_CHILD | WS_VISIBLE, (int)(winX * 0.85), (int)(winY * 0.09), 70, 25, winHwnd, (HMENU)9001, winInst, NULL);
	aboutbutton = CreateWindow(L"BUTTON", L"About", WS_CHILD | WS_VISIBLE, (int)(winX * 0.85), (int)(winY * 0.87), 70, 25, winHwnd, (HMENU)104, winInst, NULL);
	patchbutton = CreateWindow(L"BUTTON", L"Patch", WS_CHILD | WS_VISIBLE, (int)(winX * 0.85), (int)(winY * 0.15), 70, 25, winHwnd, (HMENU)9003, winInst, NULL);
	// Put in window list
	buttonList.emplace_back(browsebutton1);
	buttonList.emplace_back(browsebutton2);
	buttonList.emplace_back(aboutbutton);
	buttonList.emplace_back(patchbutton);
	windowPainter::createWindows(this);
	windowPainter::initialiseFont();
	checkboxLock();
	patchBoxLock();
	tooltipTextMaker();
	checkDirectories();
}

void Window::checkboxLock() {
	log_file << "Check if ROMs have been found." << std::endl;
	// Lock checkboxes until a bin file has been found
	if (pathFound1 || pathFound2) {
		found = TRUE;
	}
	else {
		log_file << "ROM file has not been found. Lock checkboxes." << std::endl;
		found = FALSE;
		for (int i = 0; i < windList.size(); i++) {
			LRESULT untick = SendMessage(windList[i], BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		windowSelect();
	}
	// Enable the patch window if a ROM has been found
	for (int i = 0; i < windList.size(); i++) {
		if (windList[i] == expList) {
			if (!windowHandler::expticked) {
				EnableWindow(windList[i], false);
			}
		}
		else if (windList[i] == goldList) {
			if (!windowHandler::goldticked) {
				EnableWindow(windList[i], false);
			}
		}
		else {
			EnableWindow(windList[i], found);
		}
		if (windList[i] == normalarena) {
			LRESULT tick = SendMessage(windList[i], BM_SETCHECK, BST_CHECKED, NULL);
		}
	}
}

void Window::patchBoxLock() {
	// Lock patch button until a box has been ticked
	// Check if a path is available first
	if (pathFound1 || pathFound2) {
		log_file << "Checking if an option has been ticked." << std::endl;
		for (int i = 0; i < windList.size(); i++) {
			LRESULT boxticked = SendMessage(windList[i], BM_GETCHECK, NULL, NULL);
			if (boxticked == BST_CHECKED) {
				log_file << "An option has been ticked. Unlocking patch button." << std::endl;
				checkfound = true;
			}
		}
		if (!checkfound) {
			log_file << "No options have been ticked. Locking patch button." << std::endl;
			checkfound = false;
		}
	}
	else {
		checkfound = false;
	}
	// Enable patch button if an option has been ticked
	EnableWindow(patchbutton, checkfound);
}

void Window::tooltipTextMaker() {
	// Define tool tips for each checkbox
	log_file << "Defining tooltip messages." << std::endl;
	tipDesc tips;
	// Graphics
	HWND tt_resize = toolGenerator(tips.text_resize, winHwnd, resize, winInst).hWndTT;
	HWND tt_portaits = toolGenerator(tips.text_portraits, winHwnd, portraits, winInst).hWndTT;
	HWND tt_flashes = toolGenerator(tips.text_flashes, winHwnd, flashes, winInst).hWndTT;
	HWND tt_roni = toolGenerator(tips.text_roni, winHwnd, roni, winInst).hWndTT;
	HWND tt_cafe = toolGenerator(tips.text_cafe, winHwnd, cafe, winInst).hWndTT;
	// Gameplay
	HWND tt_encounters = toolGenerator(tips.text_encounters, winHwnd, encounters, winInst).hWndTT;
	HWND tt_exp = toolGenerator(tips.text_exp, winHwnd, experience, winInst).hWndTT;
	HWND tt_expList = toolGenerator(tips.text_expList, winHwnd, expList, winInst).hWndTT;
	HWND tt_gold = toolGenerator(tips.text_gold, winHwnd, gold, winInst).hWndTT;
	HWND tt_goldList = toolGenerator(tips.text_goldList, winHwnd, goldList, winInst).hWndTT;
	HWND tt_itemspells = toolGenerator(tips.text_itemspells, winHwnd, itemspells, winInst).hWndTT;
	HWND tt_monsters = toolGenerator(tips.text_monsters, winHwnd, monsters, winInst).hWndTT;
	HWND tt_deathblows = toolGenerator(tips.text_deathblow, winHwnd, deathblows, winInst).hWndTT;
	HWND tt_cap = toolGenerator(tips.text_cap, winHwnd, cap, winInst).hWndTT;
	// Arena
	HWND tt_barena = toolGenerator(tips.text_barena, winHwnd, basicarena, winInst).hWndTT;
	HWND tt_earena = toolGenerator(tips.text_earena, winHwnd, expertarena, winInst).hWndTT;
	HWND tt_narena = toolGenerator(tips.text_narena, winHwnd, normalarena, winInst).hWndTT;
	// Story
	HWND tt_fast = toolGenerator(tips.text_fast, winHwnd, fasttext, winInst).hWndTT;
	HWND tt_script = toolGenerator(tips.text_script, winHwnd, script, winInst).hWndTT;
	HWND tt_instant = toolGenerator(tips.text_instantText, winHwnd, instant, winInst).hWndTT;
	// Audio
	HWND tt_fmvs = toolGenerator(tips.text_fmvs, winHwnd, fmvs, winInst).hWndTT;
	HWND tt_voice = toolGenerator(tips.text_voices, winHwnd, voice, winInst).hWndTT;
	HWND tt_music = toolGenerator(tips.text_music, winHwnd, music, winInst).hWndTT;
	// Mode
	HWND tt_story_mode = toolGenerator(tips.text_story_mode, winHwnd, storyMode, winInst).hWndTT;
	HWND tt_jpn_controls = toolGenerator(tips.text_jpn_control, winHwnd, jpnControls, winInst).hWndTT;
	HWND tt_bug_fix = toolGenerator(tips.text_bug_fix, winHwnd, bugFix, winInst).hWndTT;
}

void Window::checkDirectories() {
	// Check if required directories exist
	std::vector<std::string> directories;
	directories.emplace_back(gamefiles);
	directories.emplace_back(patches);
	directories.emplace_back(tools);
	boolean error = false;
	for (int i = 0; i < directories.size(); i++) {
		if (!std::filesystem::exists(directories[i])) {
			log_file << directories[i] + " is missing." << std::endl;
			error = true;
		}
	}
	if (error) {
		MessageBox(Window::winHwnd, L"Required directories are missing. Please check that gamefiles, patches, and Tools are in the same directory as the patcher before using.", L"Error", MB_ICONASTERISK);
	}
}

// Draw window
void Window::paintProcess() {
	windowPainter::paint();
}

void Window::openFile(HWND hWnd) {
	// Open ROM files
	log_file << "Open file browser." << std::endl;
	romFinder::browseFiles();
}

// Handle window selection process
void Window::windowSelect() {
	windowHandler::checkGraphics();
	windowHandler::checkGameplay();
	windowHandler::checkArena();
	windowHandler::checkStory();
	windowHandler::checkAudio();
	windowHandler::checkModes();
	if (!checkfound) {
		patchBoxLock();
	}
}

void Window::process() {
	// Check if both discs have paths available
	log_file << "Preparing to patch at " << time() << "." << std::endl;
	if (pathFound1) {
		patchProcessor::prepare(1, path1);
	}
	if (pathFound2) {
		patchProcessor::prepare(2, path2);
	}
	log_file << "Patching ended at " << time() << "." << std::endl;
}

void Window::prepareLog() {
	// Initialise log
	log_file << "Opened patcher at " << time() << "." << std::endl;
	log_file << "Current directory: " << home << std::endl;
}

std::string Window::time() {
	// Generate timeslot
	auto time = std::time(nullptr);
	auto stamp = *std::localtime(&time);
	std::ostringstream oss;
	oss << std::put_time(&stamp, "%d-%m-%Y %H-%M-%S");
	return oss.str();
}

void Window::logCommands(std::string path, std::string tool) {
	// Log contents from text files linked to external tools
	log_file << "List commands from " << tool << ":" << std::endl;
	std::ifstream openPath;
	openPath.open(path);
	std::string line;
	while (std::getline(openPath, line)) {
		log_file << line << std::endl;
	}
}

int Window::commandHandler(std::string cmd) {
	std::string tempPath = home + "\\temp.txt";
	int maxLines = 200;
	log_file << "Run " << cmd << std::endl;
	int exitCode = system((cmd).c_str());
	std::ifstream outputFile;
	outputFile.open(tempPath);
	std::string line;
	int lineCount = 0;
	while (std::getline(outputFile, line)) {
		if (lineCount < maxLines) {
			log_file << line << std::endl;
		}
		lineCount++;
	}
	if (lineCount > maxLines) {
		log_file << "... " << lineCount - maxLines << " more lines not included." << std::endl;
	}
	outputFile.close();
	std::filesystem::remove(tempPath);
	log_file << "Exit code: " << exitCode << std::endl;
	if (exitCode != 0) {
		log_file << "ERROR: Non-zero code used. Check the BIN or the rest of the log for errors." << std::endl;
	}
	return exitCode;
}

// Restores default patcher settings
void Window::restoreDefaults() {
	log_file << "Resetting file paths." << std::endl;
	path1 = "";
	path2 = "";
	pathFound1 = false;
	pathFound2 = false;
	romFinder::discFound1 = false;
	romFinder::discFound2 = false;
	windowPainter::drawDropdown("reset");
	checkboxLock();
	patchBoxLock();
	log_file << "Removing paths from windows." << std::endl;
	SetWindowText(cd1path, L"");
	SetWindowText(cd2path, L"");
}

void Window::dropdown(NMBCDROPDOWN* pDropDown, std::string option) {
	// Create dropdown menu
	dropDown = pDropDown;
	windowPainter::drawDropdown(option);	
}