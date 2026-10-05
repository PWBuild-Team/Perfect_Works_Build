#include "pch.h"
#include "romFinder.h"

void romFinder::browseFiles() {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Window::winHwnd;
	ofn.lpstrFilter = "Bin File (*.bin)\0*.bin\0";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.nMaxFile = MAX_PATH;
	char szFile[MAX_PATH];
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nFilterIndex = 1;
	if (GetOpenFileNameA(&ofn)) {
		std::string path = ofn.lpstrFile;
		Window::log_file << "File selected: " << path << std::endl;
		Window::log_file << "File size: " << std::filesystem::file_size(path) << " bytes" << std::endl;
		// Check for Xenogears bin files
		searchCD(path);
		if (getFound()) {
			Window::log_file << "Xenogears has been found. Determine disc number." << std::endl;
			Window::discNum = getDisc();
			if (discNum == 1 || discNum == 2) {
				setPathText(path, discNum);
			}
			else {
				romErrorMsg();
			}
			if (Window::pathFound1 || Window::pathFound2) {
				Window::checkboxLock();
			}
		}
		else {
			Window::log_file << "\"XENOGEARS\" was not found in the disc header, or the file size does not match the disc." << std::endl;
			romErrorMsg();
		}
	}
}

void romFinder::setPathText(std::string path, int num) {
	if (num == 1) {
		Window::log_file << "Disc 1 found." << std::endl;
		Window::pathFound1 = true;
		Window::log_file << "Determine disc 1 path." << std::endl;
		Window::path1 = path;
	}
	else if (num == 2) {
		Window::log_file << "Disc 2 found." << std::endl;
		Window::pathFound2 = true;
		Window::log_file << "Determine disc 2 path." << std::endl;
		Window::path2 = path;
	}
	std::wstring wpath = std::wstring(path.begin(), path.end());
	LPCWSTR lpath = wpath.c_str();
	if (discNum == 1) {
		Window::log_file << "Put disc 1 path in path window." << std::endl;
		SetWindowText(Window::cd1path, lpath);
	}
	else if (discNum == 2) {
		Window::log_file << "Put disc 2 path in path window." << std::endl;
		SetWindowText(Window::cd2path, lpath);
	}
}

void romFinder::romErrorMsg() {
	Window::log_file << "The selected file is not a valid Xenogears ROM." << std::endl;
	MessageBox(Window::winHwnd, L"The bin is not valid.", L"Error", MB_ICONERROR);
}

void romFinder::searchCD(std::string path) {
	// Clear results from any previously selected file
	xenoFound = false;
	discNum = 0;
	std::ifstream file;
	int byte = -1;
	file.open(path, std::ios::binary);
	while (!file.bad()) {
		file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		byte += 1;
		// Check to see if the function has passed the header
		if (file.eof() || byte > 37704) {
			break;
		}
		// Find "XENOGEARS" in the ROM header
		if (buffer == 'X') {
			xenoFound = true;
			while (!discFound1 || !discFound2) {
				file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
				byte += 1;
				if (byte == 37736) {
					findDiscNum(path);
					break;
				}
			}
		}
	}
	file.close();
}

void romFinder::findDiscNum(std::string path) {
	int val = (int)buffer;
	Window::log_file << "Disc ID byte: " << val << std::endl;
	// Determine disc number through the first file difference
	if (val == 178) {
		discNum = 1;
		discFound1 = true;
		fileSize = std::filesystem::file_size(path);
		padDisc1 = (fileSize == 718738272 - postgapBytes);
		if (padDisc1) {
			Window::log_file << "Disc 1 is missing its postgap. It will be padded when patching." << std::endl;
		}
		else if (fileSize != 718738272) {
			Window::log_file << "Disc 1 size mismatch. Expected 718738272 bytes, found " << fileSize << "." << std::endl;
			xenoFound = false;
		}
	}
	else if (val == 207) {
		discNum = 2;
		discFound2 = true;
		fileSize = std::filesystem::file_size(path);
		padDisc2 = (fileSize == 688700880 - postgapBytes);
		if (padDisc2) {
			Window::log_file << "Disc 2 is missing its postgap. It will be padded when patching." << std::endl;
		}
		else if (fileSize != 688700880) {
			Window::log_file << "Disc 2 size mismatch. Expected 688700880 bytes, found " << fileSize << "." << std::endl;
			xenoFound = false;
		}
	}
	else {
		Window::log_file << "Unknown disc ID byte. Expected 178 (disc 1) or 207 (disc 2)." << std::endl;
	}
}

bool romFinder::getFound() {
	return xenoFound;
}

int romFinder::getDisc() {
	return discNum;
}
