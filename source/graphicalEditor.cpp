#include "pch.h"
#include "graphicalEditor.h"

void graphicalEditor::battleExeEdits() {
	Window::log_file << "Applying battle executable changes." << std::endl;
	for (const auto& entry : std::filesystem::directory_iterator(applyPatch::temp)) {
		// Remove battle flashes
		std::string trimfile = gameFileTools::fileTrim(entry.path().string());
		// Check if filename is 0038
		if (trimfile != "0038") {
			continue;
		}
		// Decompress file
		std::filesystem::current_path(Window::home);
		int batch_decompress = Window::runCommand("Tools\\xenocomp.exe -d gamefiles\\temp\\0038 gamefiles\\temp\\0038.dec");
		std::filesystem::current_path(patchProcessor::gamefilePath);
		std::filesystem::current_path(applyPatch::temp);
		std::string decomp = "0038.dec";
		// Open file
		std::fstream fileContents;
		fileContents.open(decomp, std::ios::in | std::ios::out | std::ios::binary);
		// Find the position of the flash timer
		fileContents.seekp(334032, std::ios_base::beg);
		int flash = 0x00;
		fileContents.write(reinterpret_cast <char*>(&flash), 2);
		// Close file
		fileContents.close();
		// Recompress file
		std::filesystem::current_path(Window::home);
		int batch_compress = Window::runCommand("Tools\\xenocomp.exe -c gamefiles\\temp\\0038.dec gamefiles\\temp\\0038");
		// Remove decompressed file
		std::filesystem::current_path(patchProcessor::gamefilePath);
		std::filesystem::current_path(applyPatch::temp);
		remove("0038.dec");
		std::filesystem::current_path("..\\");
	}
}

