#include "pch.h"
#include "partyStatEditor.h"
#include "Window.h"

partyStatEditor::partyStatEditor() {
}

partyStatEditor::~partyStatEditor() {

}

void partyStatEditor::deathblowLevels() {
	// Decompress file
	int batch_decompress = Window::runCommand("..\\..\\Tools\\xenopack.exe -u 2607.unk4");
	std::string decomp = "file0";
	// Deathblow level data
	int dbData[9];
	popData(dbData);
	// Open file
	std::fstream fileContents;
	fileContents.open(decomp, std::ios::in | std::ios::out | std::ios::binary);
	// Edit Deathblow learning level
	for (int i = 0; i < 9; i++) {
		fileContents.seekp(dbData[i], std::ios_base::beg);
		wchar_t dbBuffer = 0x05;
		int iteration = 0;
		int val = 0x01;
		while (dbBuffer != 0x00 && dbBuffer != 0xff) {
			fileContents.seekp(dbData[i] + iteration, std::ios_base::beg);
			fileContents.write(reinterpret_cast <char*>(&val), 1);
			iteration = iteration + 1;
			fileContents.seekp(dbData[i] + iteration, std::ios_base::beg);
			fileContents.read(reinterpret_cast<char*>(&dbBuffer), 1);
		}
	}
	// Close file
	fileContents.close();
	// Recompress file
	int batch_compress = Window::runCommand("..\\..\\Tools\\xenopack.exe -p 2607.unk4");
	// Remove decompressed files
	remove("file0"), remove("file1"), remove("file2"), remove("file3");
}

void partyStatEditor::popData(int dbData[]) {
	dbData[0] = 0x100;
	dbData[1] = 0x210;
	dbData[2] = 0x320;
	dbData[3] = 0x430;
	dbData[4] = 0x540;
	dbData[5] = 0x650;
	dbData[6] = 0x760;
	dbData[7] = 0xa90;
	dbData[8] = 0xba0;
}