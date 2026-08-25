#include "pch.h"
#include "patchProcessor.h"

void patchProcessor::prepare(int discNum, std::string path) {
	num = discNum;
	filePath = path;
	SetWindowText(Window::winHwnd, L"Preparing...");
	// Work around path names with whitespace.
	Window::log_file << "Check if disc filename has whitespace characters." << std::endl;
	if (path.find(' ') != std::string::npos) {
		Window::log_file << "Whitespace characters found. Creating a copy of the ROM inside the home directory." << std::endl;
		removeWhitespace();
	}
	std::filesystem::current_path(Window::home);
	if (gamefileVerify()) {
		// Check for ticked boxes
		patchVerifier::verify();
	}
	initialisePatchLists();
	if (filePathValid) {
		Window::log_file << "Check if the patcher is inside OneDrive." << std::endl;;
		if (oneDriveCheck()) {
			start();
		}
	}
	else {
		MessageBox(Window::winHwnd, L"Could not find directory for 'gamefiles'. Check repo for latest version.", L"Error", MB_ICONERROR);
	}
}

void patchProcessor::removeWhitespace() {
	SetWindowText(Window::winHwnd, L"Copying files...");
	std::filesystem::current_path(Window::home);
	std::string curPath;
	if (num == 1) {
		tempPath = "Xenogears1.bin";
	}
	if (num == 2) {
		tempPath = "Xenogears2.bin";
	}
	std::ifstream src(filePath, std::ios::binary);
	std::ofstream dst(tempPath, std::ios::binary);
	dst << src.rdbuf();
	Window::log_file << "Copying completed." << std::endl;
	space = true;
}

bool patchProcessor::gamefileVerify() {
	// Access directory for files
	Window::log_file << "Check if 'gamefiles' directory is valid." << std::endl;
	if (std::filesystem::exists(gamefilePath)) {
		Window::log_file << "'gamefiles' directory is valid." << std::endl;
		std::filesystem::current_path(gamefilePath);
		filePathValid = true;
	}
	return filePathValid;
}

// Initialise patch list
void patchProcessor::initialisePatchLists() {
	Window::log_file << "Initialise patch names." << std::endl;
	patchList.emplace_back(expName);
	patchList.emplace_back(goldName);
	patchList.emplace_back(bugName);
	patchList.emplace_back(itemspellsName);
	patchList.emplace_back(scriptName);
	patchList.emplace_back(jpnName);
	patchList.emplace_back(encountersName);
	patchList.emplace_back(fmvName);
	patchList.emplace_back(fmvPatch);
	patchList.emplace_back(storyModeName);
	patchList.emplace_back(resizeName);
	patchList.emplace_back(portraitsName);
	patchList.emplace_back(monsterName);
	patchList.emplace_back(musicName);
	patchList.emplace_back(arenaName);
	patchList.emplace_back(fastName);
	patchList.emplace_back(voiceName);
	patchList.emplace_back(titleName);
	patchList.emplace_back(roniName);
	patchList.emplace_back(cafeName);
	patchList.emplace_back(deathblowName);
}

bool patchProcessor::oneDriveCheck() {
	bool safeDrive = false;
	if (Window::home.contains("OneDrive")) {
		Window::log_file << "Display OneDrive error." << std::endl;
		MessageBox(Window::winHwnd, L"The patcher is in the OneDrive. It cannot be used.", L"Error", MB_ICONASTERISK);
		Window::log_file << "Abort patching process." << std::endl;
		SetWindowText(Window::winHwnd, Window::title);
	}
	else {
		Window::log_file << "OneDrive is not in use. Resume execution." << std::endl;
		safeDrive = true;
	}
	return safeDrive;
}

void patchProcessor::start() {
	Window::log_file << "Starting patch process." << std::endl;
	SetWindowText(Window::winHwnd, L"Patching...");
	Window::log_file << "Changing cursor to reflect loading." << std::endl;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	// Apply patches
	Window::log_file << "Applying patches." << std::endl;
	applyPatch::initialise();
	if (applyPatch::patch()) {
		Window::log_file << "xenoiso process successful." << std::endl;
		successMessage = true;
	}
	else {
		Window::log_file << "xenoiso process failed." << std::endl;
		successMessage = false;
	}
	reinitialisePatches();
	clearPatchLists();
	if (num == 1) {
		if (!Window::pathFound2) {
			finish();
		}
	}
	else {
		finish();
	}
}

void patchProcessor::finish() {
	SetWindowText(Window::winHwnd, Window::title);
	if (successMessage) {
		Window::log_file << "Show success message." << std::endl;
		MessageBox(Window::winHwnd, L"Patch was completed successfully. The completed ROM will be available as Xenogears_PW_CD1 or Xenogears_PW_CD2.", L"Success", MB_ICONASTERISK);
	}
	else {
		Window::log_file << "Show failure message." << std::endl;
		MessageBox(Window::winHwnd, L"An error occurred with xenoiso. View pw_log for details.", L"Error", MB_ICONASTERISK);
	}
	for (int i = 0; i < patchList.size(); i++) {
		Window::log_file << patchList[i] << std::endl;
	}
	// Restore defaults
	Window::restoreDefaults();
}

// Removes patch names
void patchProcessor::reinitialisePatches() {
	Window::log_file << "Clearing patch names." << std::endl;
	encountersName = "";
	expName = "";
	fastName = "";
	fmvName = "";
	roniName = "";
	itemspellsName = "";
	monsterName = "";
	resizeName = "";
	scriptName = "";
	arenaName = "";
	portraitsName = "";
	bugName = "";
	titleName = "";
	voiceName = "";
	flashesName = "";
	storyModeName = "";
	goldName = "";
	fmvPatch = "";
	cafeName = "";
	deathblowName = "";
	jpnName = "";
	musicName = "";
}

// Clear patch lists
void patchProcessor::clearPatchLists() {
	Window::log_file << "Clearing patch lists." << std::endl;
	patchList.clear();
}