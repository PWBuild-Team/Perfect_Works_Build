#include "fileSystemTools.h"

void fileSystemTools::toTemp() {
	std::filesystem::current_path(Window::home);
	std::filesystem::current_path(patchProcessor::gamefilePath);
	std::filesystem::current_path(applyPatch::temp);
}

