#include "pch.h"
#include "patchProcessor.h"

void patchProcessor::prepare(int discNum, std::string path) {
	num = discNum;
	filePath = path;
	space = false;
	bool needsPostgap = (discNum == 1) ? romFinder::padDisc1 : romFinder::padDisc2;
	Window::log_file << "Preparing disc " << discNum << " from " << path << std::endl;
	SetWindowText(Window::winHwnd, L"Preparing...");
	// Work around path names with whitespace.
	Window::log_file << "Check if disc filename has whitespace characters." << std::endl;
	if (path.find(' ') != std::string::npos) {
		Window::log_file << "Whitespace characters found. Creating a copy of the ROM inside the home directory." << std::endl;
		removeWhitespace();
	}
	else if (needsPostgap) {
		// Never modify the user's ROM. Pad a copy instead.
		Window::log_file << "Creating a copy of the ROM inside the home directory to pad." << std::endl;
		removeWhitespace();
	}
	if (needsPostgap) {
		appendPostgap();
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

// Append the 2-second (150 sector) postgap that some dumps omit
void patchProcessor::appendPostgap() {
	SetWindowText(Window::winHwnd, L"Padding ROM...");
	const int sectorSize = 2352;
	const int gapSectors = romFinder::postgapBytes / sectorSize;
	std::fstream rom(tempPath, std::ios::binary | std::ios::in | std::ios::out);
	// Continue the sector addresses (BCD minute/second/frame) from the last sector
	unsigned char header[16];
	rom.seekg(-sectorSize, std::ios::end);
	rom.read(reinterpret_cast<char*>(header), sizeof(header));
	auto fromBcd = [](unsigned char b) { return (b >> 4) * 10 + (b & 0x0F); };
	auto toBcd = [](int v) { return static_cast<char>(((v / 10) << 4) | (v % 10)); };
	int lastFrame = (fromBcd(header[12]) * 60 + fromBcd(header[13])) * 75 + fromBcd(header[14]);
	rom.seekp(0, std::ios::end);
	for (int i = 1; i <= gapSectors; i++) {
		// Empty mode 2 sector as in Redump dumps: sync pattern, address and mode,
		// with the subheader and data left as zero
		std::vector<char> sector(sectorSize, 0);
		std::fill(sector.begin() + 1, sector.begin() + 11, static_cast<char>(0xFF));
		int frame = lastFrame + i;
		sector[12] = toBcd(frame / 4500);
		sector[13] = toBcd((frame / 75) % 60);
		sector[14] = toBcd(frame % 75);
		sector[15] = 2;
		rom.write(sector.data(), sectorSize);
	}
	// Flush the last sectors to disk before reading the final size
	rom.close();
	Window::log_file << "Postgap appended. ROM size: " << std::filesystem::file_size(tempPath) << std::endl;
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
	patchList.emplace_back(metricsName);
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
	Window::log_file << "Selected patch directories:" << std::endl;
	for (const auto& patch : patchList) {
		if (patch != "") {
			Window::log_file << "  " << patch << std::endl;
		}
	}
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
	metricsName = "";
}

// Clear patch lists
void patchProcessor::clearPatchLists() {
	Window::log_file << "Clearing patch lists." << std::endl;
	patchList.clear();
}