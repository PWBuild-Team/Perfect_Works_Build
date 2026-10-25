#include "pch.h"
#include "metricEditor.h"


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

void metricEditor::editStatus(std::string language) {
	fileSystemTools::toTemp();
	std::string menuFile = "2593.unk8";
	handleReplace(menuFile, language);
	menuFile = "3958.unk8";
	handleReplace(menuFile, language);
	std::filesystem::current_path("..\\");
}

void metricEditor::handleReplace(std::string menuFile, std::string language) {
	// Decompress file
	if (menuFile == "2593.unk8") {
		int batch_decompress = system("..\\..\\Tools\\xenopack.exe -u 2593.unk8");
	}
	if (menuFile == "3958.unk8") {
		int batch_decompress = system("..\\..\\Tools\\xenopack.exe -u 3958.unk8");
	}
	// Copy menu text
	if (language == "en") {
		std::filesystem::copy("..\\metric_subfiles\\en_2593_3958\\file2", "file2", std::filesystem::copy_options::overwrite_existing);
	}
	if (language == "jp") {
		std::filesystem::copy("..\\metric_subfiles\\jp_2593_3958\\file2", "file2", std::filesystem::copy_options::overwrite_existing);
	}
	// Recompress file
	if (menuFile == "2593.unk8") {
		int batch_recompress = system("..\\..\\Tools\\xenopack.exe -p 2593.unk8");
	}
	if (menuFile == "3958.unk8") {
		int batch_recompress = system("..\\..\\Tools\\xenopack.exe -p 3958.unk8");
	}
	// Remove decompressed files
	remove("file0"), remove("file1"), remove("file2"), remove("file3"), remove("file4"), remove("file5"), remove("file6"), remove("file7");

}