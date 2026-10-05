#include "pch.h"
#include "applyPatch.h"

void applyPatch::initialise() {
	Window::log_file << "Initialise patched ROM name and disc number to pass to xenoiso." << std::endl;
	// Disc 1 data
	if (patchProcessor::num == 1) {
		fileName = "Xenogears_PW_CD1.bin";
		cueName = "Xenogears_PW_CD1.cue";
		cdName = "cd1";
	}
	// Disc 2 data
	if (patchProcessor::num == 2) {
		fileName = "Xenogears_PW_CD2.bin";
		cueName = "Xenogears_PW_CD2.cue";
		cdName = "cd2fix";
	}
	if (patchProcessor::space) {
		oldPath = patchProcessor::tempPath;
	}
	else {
		oldPath = patchProcessor::filePath;
	}
	// Return to home directory
	std::filesystem::current_path(Window::home);
}

bool applyPatch::patch() {
	prepareFiles();
	executeBat();
	if (patchProcessor::fmvName != "") {
		fileEditor::editSLUS(fileName);
	}
	cleanup();
	makeCue();
	Window::log_file << "Check filesize to determine if xenoiso executed successfully." << std::endl;
	if (!std::filesystem::exists(fileName)) {
		Window::log_file << fileName << " was not created. Returning error." << std::endl;
		return false;
	}
	int fileSize = std::filesystem::file_size(fileName);
	Window::log_file << fileName << " size: " << fileSize << " bytes" << std::endl;
	if (fileSize == 0) {
		Window::log_file << "Failure to execute xenoiso. Returning error." << std::endl;
		return false;
	}
	else {
		Window::log_file << "xenoiso executed successfully. Returning completion message." << std::endl;
		return true;
	}
}

void applyPatch::prepareFiles() {
	// Detect if the patched ROM already exists.
	Window::log_file << "Check if a patched ROM already exists." << std::endl;
	if (std::filesystem::exists(fileName)) {
		Window::log_file << "Deleting existing patched ROM." << std::endl;
		remove(fileName.c_str());
	}
	Window::log_file << "Creating list file for xenoiso." << std::endl;
	list_file.open("list.txt", std::ios::trunc);
	Window::log_file << "Creating xdelta command file." << std::endl;
	batch_file.open("commands.cmd", std::ios::trunc);
	if (!patchProcessor::patchList.empty()) {
		createTemp();
		std::filesystem::current_path(Window::home);
		if (patchProcessor::fmvName != "") {
			applyFMV();
		}
		if (patched) {
			backupROM();
		}
		Window::log_file << "Write list file for xenoiso." << std::endl;
		list_file << cdName << "\n" << oldPath << "\n" << fileName << "\n" << "-1,.\\gamefiles\\temp" << std::flush;
	}
	list_file.close();
	batch_file.close();
}

void applyPatch::createTemp() {
	// Create ROMs using xenoiso
	Window::log_file << "Create temporary directory." << std::endl;
	std::filesystem::current_path(patchProcessor::gamefilePath);
	std::filesystem::create_directory(temp);
	Window::log_file << "Copy files from each selected option into the temporary directory." << std::endl;
	for (int i = 0; i < patchProcessor::patchList.size(); i++) {
		if (patchProcessor::patchList[i] != "" && patchProcessor::patchList[i] != patchProcessor::fmvPatch) {
			if (patchProcessor::patchList[i] == patchProcessor::fastName || patchProcessor::patchList[i] == patchProcessor::jpnName) {
				// Copy executable to temp
				if (!windowHandler::fmvticked == BST_CHECKED) {
					if (patchProcessor::num == 1) {
						std::filesystem::copy(patchProcessor::exeName1, temp, std::filesystem::copy_options::update_existing);
					}
					if (patchProcessor::num == 2) {
						std::filesystem::copy(patchProcessor::exeName2, temp, std::filesystem::copy_options::update_existing);
					}
					if (windowHandler::fastticked == BST_CHECKED) {
						Window::log_file << "Applying text speed change to game's executable." << std::endl;
						for (const auto& entry : std::filesystem::directory_iterator(temp)) {
							fileEditor::exeEdits(entry.path().string());
						}
					}
				}
			}
			std::filesystem::copy(patchProcessor::patchList[i], temp, std::filesystem::copy_options::overwrite_existing);
		}
	}
	if (patchProcessor::editExe) {
		// Copy executable to temp
		if (!windowHandler::fmvticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				std::filesystem::copy(patchProcessor::exeName1, temp, std::filesystem::copy_options::update_existing);
			}
			if (patchProcessor::num == 2) {
				std::filesystem::copy(patchProcessor::exeName2, temp, std::filesystem::copy_options::update_existing);
			}
		}
	}
	iterateTemp();
}

void applyPatch::iterateTemp() {
	fileEditor::graphicEdits();
	fileEditor::gameplayEdits();
	fileEditor::scriptEdits();
	fileEditor::audioEdits();
	fileEditor::modeEdits();
}

void applyPatch::applyFMV() {
	Window::log_file << "Applying FMV undub." << std::endl;
	std::filesystem::current_path(Window::home);
	Window::log_file << "Creating batch file commands." << std::endl;
	if (patched) {
		// Create copy of bin file to stack patches
		Window::log_file << "Make backup of the ROM if it has already been patched." << std::endl;
		batch_file << "copy \"" + fileName + "\" backup.bin \n" << std::endl;
		batch_file << "del \"" + fileName + "\" \n" << std::endl;
		batch_file << "Tools\\xdelta3-3.0.11-i686.exe -d  -s backup.bin patches\\" + patchProcessor::fmvPatch + " \"" + fileName + "\" \n" << std::endl;
	}
	else {
		batch_file << "Tools\\xdelta3-3.0.11-i686.exe -d  -s \"" + oldPath + "\" patches\\" + patchProcessor::fmvPatch + " \"" + fileName + "\" \n" << std::endl;
		patched = true;
	}
	if (patchProcessor::num == 1) {
		batch_file << "Tools\\Insert_log_file.exe " + fileName + " Tools\\xenocd1_softmod_files_extended.txt -new" << std::endl;
	}
	if (patchProcessor::num == 2) {
		batch_file << "Tools\\Insert_log_file.exe " + fileName + " Tools\\xenocd2_softmod_files_extended.txt -new" << std::endl;
	}
}

void applyPatch::backupROM() {
	Window::log_file << "Create a backup ROM if the FMV patch has been applied." << std::endl;
	oldPath = "backup.bin";
	batch_file << "copy \"" + fileName + "\" " + oldPath + "\n" << std::endl;
	batch_file << "del \"" + fileName + "\" \n" << std::endl;
}

void applyPatch::executeBat() {
	// Execute patch file
	if (patchProcessor::fmvName != "") {
		Window::log_file << "Executing batch file. Applying FMV patch and rewriting the file table." << std::endl;
		Window::logFileContents("commands.cmd");
		int batch_exit_code = Window::runCommand("cmd.exe /c .\\commands.cmd");
	}
	Window::log_file << "Execute xenoiso." << std::endl;
	Window::logFileContents("list.txt");
	try {
		// Detect errors with xenoiso
		int batch_exit_code = Window::runCommand("cmd.exe /c Tools\\xenoiso list.txt");
	}
	catch (const std::system_error& error) {
		// Catch errors when opening xenoiso
		Window::log_file << &error << std::endl;
	}
}

void applyPatch::cleanup() {
	// Reinitialise variables
	patched = false;
	// Remove batch and backup bin
	Window::log_file << "Remove command file." << std::endl;
	remove("commands.cmd");
	Window::log_file << "Remove backup ROM." << std::endl;
	remove("backup.bin");
	Window::log_file << "Remove xenoiso list." << std::endl;
	remove("list.txt");
	std::filesystem::current_path(patchProcessor::gamefilePath);
	Window::log_file << "Remove temp directory." << std::endl;
	std::filesystem::remove_all("temp");
	Window::log_file << "Remove renamed ROMs." << std::endl;
	std::filesystem::current_path(Window::home);
	if (patchProcessor::num == 1) {
		std::filesystem::remove("Xenogears1.bin");
	}
	if (patchProcessor::num == 2) {
		std::filesystem::remove("Xenogears2.bin");
	}
}

void applyPatch::makeCue() {
	// Create cue file
	Window::log_file << "Create cue file." << std::endl;
	cue_stream.open(cueName, std::ios::out);
	cue_stream << "FILE \"" + fileName + "\" BINARY" << "\n";
	cue_stream << "  TRACK 01 MODE2/2352" << "\n";
	cue_stream << "    INDEX 01 00:00:00" << "\n";
	cue_stream.close();
}
	