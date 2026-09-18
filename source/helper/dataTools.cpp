#include "dataTools.h"

std::vector<int> dataTools::popOffset(std::string dataFile) {
	std::string line;
	std::fstream exedata;
	std::vector<int> offsets;
	exedata.open(dataFile);
	while (getline(exedata, line)) {
		int pos = line.find(",");
		std::string offset = line.substr(0, pos);
		offsets.emplace_back(stoi(line));
	}
	exedata.close();
	return offsets;
}

std::vector<int> dataTools::popValues(std::string dataFile) {
	std::string line;
	std::fstream exedata;
	std::vector<int> values;
	exedata.open(dataFile);
	while (getline(exedata, line)) {
		int pos = line.find(",");
		std::string value = line.substr(pos + 1);
		values.emplace_back(stoi(value, nullptr, 16));
	}
	exedata.close();
	return values;
}