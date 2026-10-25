#include "gameFileTools.h"

std::string gameFileTools::fileTrim(std::string file) {
	std::string trimfile = file;
	trimfile.erase(0, 5);
	return trimfile;
}

std::string gameFileTools::musicfileTrim(std::string file) {
	std::string trimfile = file;
	trimfile.erase(0, 6);
	return trimfile;
}

void gameFileTools::remove2614Decomp() {
	// Remove decompressed files
	for (int i = 0; i < 38; i++) {
		std::string num = std::to_string(i);
		std::string fileName = "file" + num;
		remove(fileName.c_str());
	}
}