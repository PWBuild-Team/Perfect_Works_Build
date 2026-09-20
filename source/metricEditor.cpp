#include "pch.h"
#include "metricEditor.h"

void metricEditor::process() {
	decompMenuEdit();
	compMenuEdit();
}

void metricEditor::decompMenuEdit() {
	std::filesystem::current_path(Window::home);
	std::string file = "2597";
	editExe(file);
}

void metricEditor::compMenuEdit() {
	std::filesystem::current_path(Window::home);
	// Decompress menu file
	int batch_decompress = system("Tools\\xenocomp.exe -d gamefiles\\temp\\3957 gamefiles\\temp\\3957.dec");
	std::string file = "3957.dec";
	editExe(file);
	std::filesystem::current_path(Window::home);
	int batch_compress = system("Tools\\xenocomp.exe -c gamefiles\\temp\\3957.dec gamefiles\\temp\\3957");
	// Remove decompressed file
	std::filesystem::current_path(patchProcessor::gamefilePath);
	std::filesystem::current_path(applyPatch::temp);
	remove("3957.dec");
	std::filesystem::current_path("..\\");
}

void metricEditor::editExe(std::string file) {
	// Read data documenting menu exe differences and put it into vectors
	std::vector<int> offsets = dataTools::popOffset(menuexe);
	std::vector<int> values = dataTools::popValues(menuexe);
	// Open file
	std::filesystem::current_path(patchProcessor::gamefilePath);
	std::filesystem::current_path(applyPatch::temp);
	std::fstream fileContents;
	fileContents.open(file, std::ios::in | std::ios::out | std::ios::binary);
	// Edit file
	for (int i = 0; i < offsets.size(); i++) {
		fileContents.seekp(offsets[i], std::ios_base::beg);
		fileContents.write(reinterpret_cast <char*>(&values[i]), 1);
	}
	fileContents.close();
	std::filesystem::current_path("..\\");
}