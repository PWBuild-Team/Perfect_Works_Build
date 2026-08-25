#include "pch.h"
#include "gameplayFileEditor.h"

void gameplayFileEditor::expRateEdits(std::string file) {
	std::string trimfile = gameFileTools::fileTrim(file);
	// Check if filename is 2607
	if (trimfile != "2607.unk4") {
		return;
	}
	std::filesystem::current_path(Window::home);
	std::filesystem::current_path(patchProcessor::gamefilePath);
	std::filesystem::current_path(applyPatch::temp);
	partyStatEditor pse;
	pse.deathblowLevels();
	std::filesystem::current_path("..\\");
}

void gameplayFileEditor::removeCap(std::string file) {
	// Remove battle cap
	std::string trimfile = gameFileTools::fileTrim(file);
	// Check if filename is 0038
	if (trimfile == "0038") {
		// Decompress file
		std::filesystem::current_path(Window::home);
		int batch_decompress = system("Tools\\xenocomp.exe -d gamefiles\\temp\\0038 gamefiles\\temp\\0038.dec");
		std::filesystem::current_path(patchProcessor::gamefilePath);
		std::filesystem::current_path(applyPatch::temp);
		std::string decomp = "0038.dec";
		// Open file
		std::fstream fileContents;
		fileContents.open(decomp, std::ios::in | std::ios::out | std::ios::binary);
		// Find the position of damage caps
		int removeCap = 0x00;
		fileContents.seekp(154460, std::ios_base::beg);
		fileContents.write(reinterpret_cast <char*>(&removeCap), 4);
		fileContents.seekp(186400, std::ios_base::beg);
		fileContents.write(reinterpret_cast <char*>(&removeCap), 4);
		// Close file
		fileContents.close();
		// Recompress file
		std::filesystem::current_path(Window::home);
		int batch_compress = system("Tools\\xenocomp.exe -c gamefiles\\temp\\0038.dec gamefiles\\temp\\0038");
		// Remove decompressed file
		std::filesystem::current_path(patchProcessor::gamefilePath);
		std::filesystem::current_path(applyPatch::temp);
		remove("0038.dec");
		std::filesystem::current_path("..\\");
	}
}

void gameplayFileEditor::battleFileEdits() {
	fileSystemTools::toTemp();
	// Decompress file
	int batch_decompress = system("..\\..\\Tools\\xenopack.exe -u 2614");
	// Copy item files
	// Characters
	for (int i = 4; i < 15; i++) {
		std::filesystem::copy("..\\item_subfiles\\2614\\file" + std::to_string(i), "file" + std::to_string(i), std::filesystem::copy_options::overwrite_existing);
	}
	// Gears
	for (int i = 16; i < 33; i++) {
		std::filesystem::copy("..\\item_subfiles\\2614\\file" + std::to_string(i), "file" + std::to_string(i), std::filesystem::copy_options::overwrite_existing);
	}
	// Other
	for (int i = 36; i < 38; i++) {
		std::filesystem::copy("..\\item_subfiles\\2614\\file" + std::to_string(i), "file" + std::to_string(i), std::filesystem::copy_options::overwrite_existing);
	}
	// Recompress file
	int batch_recompress = system("..\\..\\Tools\\xenopack.exe -p 2614");
	gameFileTools::remove2614Decomp();
	std::filesystem::current_path("..\\");
}