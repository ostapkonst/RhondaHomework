#pragma once

#include <string>
#include <fstream>

static std::string gen_random(int random_len) {
	std::string tmp_s;

	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	tmp_s.reserve(random_len);

	for (int i = 0; i < random_len; ++i) 
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

	return tmp_s;
}

static bool is_file_exist(const std::string &fileName) {
	std::ifstream infile(fileName.c_str());
	bool exist = infile.good();
	infile.close();
	return exist;
}

static void create_file(const std::string &fileName) {
	std::ofstream outfile(fileName.c_str());
	outfile.close();
}

std::string gen_tmp_file(const std::string &tmp_folder, int len = 10) {
	while (true) {
		std::string tmp_filename = tmp_folder + gen_random(len) + ".tmp";
		if (!is_file_exist(tmp_filename)) {
			create_file(tmp_filename);
			return tmp_filename;
		}
	}
}
