#include "pch.h"
#include "fileEditor.h"

void fileEditor::graphicEdits() {
	if (windowHandler::flashesticked == BST_CHECKED) {
		// Remove battle flashes
		graphicalEditor::battleExeEdits();
	}
}

void fileEditor::gameplayEdits() {
	if (patchProcessor::expName != "" || patchProcessor::goldName != "") {
		// Iterate through enemy files to apply exp or gold changes
		monsterEditor::verifyFiles();
	}
	if (windowHandler::deathblowsticked == BST_CHECKED) {
		Window::log_file << "Applying ability learning level changes." << std::endl;
		for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
			gameplayFileEditor::expRateEdits(entry.path().string());
		}
	}
	if (windowHandler::capticked == BST_CHECKED) {
		Window::log_file << "Removing damage cap." << std::endl;
		for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
			gameplayFileEditor::removeCap(entry.path().string());
		}
	}
	if (windowHandler::itemspellsticked == BST_CHECKED) {
		gameplayFileEditor::battleFileEdits();
	}
}

void fileEditor::scriptEdits() {
	if (windowHandler::fastticked == BST_CHECKED || windowHandler::instantticked == BST_CHECKED) {
		if (!windowHandler::fmvticked == BST_CHECKED) {
			Window::log_file << "Applying text speed change to game's executable." << std::endl;
			for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
				exeEdits(entry.path().string());
			}
		}
	}
	if (windowHandler::scriptticked == BST_CHECKED) {
		fileSystemTools::toTemp();
		// Decompress file
		int batch_decompress = system("..\\..\\Tools\\xenopack.exe -u 2614");
		// Copy script files
		std::filesystem::copy("..\\script_subfiles\\2614\\file37", "file37", std::filesystem::copy_options::overwrite_existing);
		// Recompress file
		int batch_recompress = system("..\\..\\Tools\\xenopack.exe -p 2614");
		gameFileTools::remove2614Decomp();
		std::filesystem::current_path("..\\");
	}
}

void fileEditor::audioEdits() {
	if (windowHandler::musicticked == BST_CHECKED) {
		if (windowHandler::scriptticked == BST_CHECKED || windowHandler::fastticked == BST_CHECKED || (windowHandler::basicarenaticked || windowHandler::expertarenaticked)) {
			Window::log_file << "Applying music placement edits." << std::endl;
			std::vector<std::string> musicFileList;
			std::string musicdir = "";
			if (patchProcessor::num == 1) {
				musicdir = "music_1";
			}
			if (patchProcessor::num == 2) {
				musicdir = "music_2";
			}
			for (const auto& musicentry : std::filesystem::directory_iterator(musicdir)) {
				std::string trimfile = gameFileTools::musicfileTrim(musicentry.path().string());
				musicFileList.emplace_back(trimfile);
			}
			for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
				std::string trimfile = gameFileTools::fileTrim(entry.path().string());
				if (std::find(musicFileList.begin(), musicFileList.end(), trimfile) != musicFileList.end()) {
					audioEditor::musicEdits(entry.path().string());
				}
			}
		}
	}
}

void fileEditor::modeEdits() {
	if (windowHandler::jpnticked == BST_CHECKED) {
		Window::log_file << "Applying Japanese control changes." << std::endl;
		for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
			controlEditor::addImage(entry.path().string());
			if (!windowHandler::fmvticked == BST_CHECKED) {
				controlEditor::editExecutable(entry.path().string());
			}
			controlEditor::editBattleExe(entry.path().string());
		}
	}
	if (windowHandler::storymodeticked == BST_CHECKED) {
		fileSystemTools::toTemp();
		// Decompress file
		int batch_decompress = system("..\\..\\Tools\\xenopack.exe -u 2614");
		// Copy script files
		std::filesystem::copy("..\\sm_subfiles\\2614\\file3", "file3", std::filesystem::copy_options::overwrite_existing);
		// Recompress file
		int batch_recompress = system("..\\..\\Tools\\xenopack.exe -p 2614");
		gameFileTools::remove2614Decomp();
		std::filesystem::current_path("..\\");
	} 
}

void fileEditor::editSLUS(std::string romFile) {
	// Insert new SLUS
	if (patchProcessor::editExe) {
		// Add fast text to softsubs SLUS
		std::filesystem::current_path(patchProcessor::gamefilePath);
		if (patchProcessor::num == 1) {
			std::filesystem::copy(patchProcessor::slusDisc1, applyPatch::temp, std::filesystem::copy_options::update_existing);
		}
		if (patchProcessor::num == 2) {
			std::filesystem::copy(patchProcessor::slusDisc2, applyPatch::temp, std::filesystem::copy_options::update_existing);
		}
		if (patchProcessor::jpnName != "") {
			Window::log_file << "Applying control edits to game's executable." << std::endl;
			for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
				controlEditor::editExecutable(entry.path().string());
			}
		}
		if (windowHandler::fastticked == BST_CHECKED || windowHandler::instantticked == BST_CHECKED) {
			Window::log_file << "Applying text speed change to game's executable." << std::endl;
			for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
				exeEdits(entry.path().string());
			}
		}
		if (windowHandler::capticked == BST_CHECKED) {
			Window::log_file << "Removing damage cap." << std::endl;
			for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
				gameplayFileEditor::removeCap(entry.path().string());
			}
		}
		std::filesystem::current_path(Window::home);
	}
	// Create batch file to make a new SLUS
	makeSLUS(romFile);
}

void fileEditor::makeSLUS(std::string romFile) {
	std::ofstream batch_file2;
	Window::log_file << "Creating new SLUS file." << std::endl;
	batch_file2.open("commands2.cmd", std::ios::trunc);
	if (patchProcessor::num == 1) {
		if (patchProcessor::editExe) {
			batch_file2 << "Tools\\Xeno_slus_ins.exe " + romFile + " gamefiles\\temp\\SLUS_006.64" << std::endl;
		}
		else {
			batch_file2 << "Tools\\Xeno_slus_ins.exe " + romFile + " gamefiles\\sub_executable\\disc1\\SLUS_006.64" << std::endl;
		}
	}
	if (patchProcessor::num == 2) {
		if (patchProcessor::editExe) {
			batch_file2 << "Tools\\Xeno_slus_ins.exe " + romFile + " gamefiles\\temp\\SLUS_006.69" << std::endl;
		}
		else {
			batch_file2 << "Tools\\Xeno_slus_ins.exe " + romFile + " gamefiles\\sub_executable\\disc2\\SLUS_006.69" << std::endl;
		}
	}
	batch_file2.close();
	int batch_exit_code = system("cmd.exe /c commands2.cmd");
	Window::log_file << "Remove new SLUS command file." << std::endl;
	remove("commands2.cmd");
}

void fileEditor::exeEdits(std::string file) {
	std::string trimfile = gameFileTools::fileTrim(file);
	if (patchProcessor::fmvName == "") {
		if (patchProcessor::num == 1) {
			// Check if filename is 0022
			if (trimfile != "0022") {
				return;
			}
		}
		if (patchProcessor::num == 2) {
			// Check if filename is 0017
			if (trimfile != "0017") {
				return;
			}
		}
	}
	else {
		if (patchProcessor::num == 1) {
			// Check if filename is SLUS_006.64
			if (trimfile != "SLUS_006.64") {
				return;
			}
		}
		if (patchProcessor::num == 2) {
			// Check if filename is SLUS_006.69
			if (trimfile != "SLUS_006.69") {
				return;
			}
		}
	}
	editTextSpeed(file);
}

void fileEditor::editTextSpeed(std::string file) {
	// Open file
	std::fstream fileContents;
	fileContents.open(file, std::ios::in | std::ios::out | std::ios::binary);
	// Find the position of the text speed value
	fileContents.seekp(151908, std::ios_base::beg);
	int speed;
	if (windowHandler::fastticked == BST_CHECKED) {
		speed = 0x05;
	}
	if (windowHandler::instantticked == BST_CHECKED) {
		speed = 0xFF;
	}
	fileContents.write(reinterpret_cast <char*>(&speed), 2);
	fileContents.seekp(151911, std::ios_base::beg);
	int nextval = 0x34;
	fileContents.write(reinterpret_cast <char*>(&nextval), 2);
	// Close file
	fileContents.close();
}

