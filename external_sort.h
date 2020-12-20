#pragma once

#include <fstream>
#include <string>

#include "filename_gen.h"

template <typename T>
class ExternalSort {
private:
	std::string inp_file;
	std::string out_file;
	std::string tmp1_file;
	std::string tmp2_file;

	bool natural_split_step(std::ifstream &inp_fs, std::ofstream &tmp_fs1, std::ofstream &tmp_fs2);

	void natural_merge_step(std::ofstream &out_fs, std::ifstream &tmp_fs1, std::ifstream &tmp_fs2);

	T sync_sequences(std::ifstream &inp_fs, std::ofstream &out_fs, T num);

	void finish_sequences(std::ifstream &inp_fs, std::ofstream &out_fs, T num);
public:
	ExternalSort(
		const std::string &input_file,
		const std::string &output_file,
		const std::string &temp_folder) 
	{
		inp_file = input_file;
		out_file = output_file;

		tmp1_file = gen_tmp_file(temp_folder);
		tmp2_file = gen_tmp_file(temp_folder);
	};

	~ExternalSort() {
#ifndef DEBUG
		std::remove(tmp1_file.c_str());
		std::remove(tmp2_file.c_str());
#endif
	};

	void natural_sort();
};

template <typename T>
T ExternalSort<T>::sync_sequences(std::ifstream &inp_fs, std::ofstream &out_fs, T num) {
	out_fs << num << std::endl;
	T prev_num = num;

	while (inp_fs >> num && !(num < prev_num)) {
		out_fs << num << std::endl;
		prev_num = num;
	}

	return num;
};

template <typename T>
void ExternalSort<T>::finish_sequences(std::ifstream &inp_fs, std::ofstream &out_fs, T num) {
	if (!inp_fs.good()) return;

	out_fs << num << std::endl;
	while (inp_fs >> num) 
		out_fs << num << std::endl;
}

template <typename T>
bool ExternalSort<T>::natural_split_step(
		std::ifstream &inp_fs,
		std::ofstream &tmp_fs1,
		std::ofstream &tmp_fs2)
{
	T num, prev_num;
	bool first_run = true, to_first_file = true;
	int swap_count = 0;

	while (inp_fs >> num) {
		if (first_run) 
			first_run = false;
		else
			if (num < prev_num) {
				to_first_file = !to_first_file;
				swap_count = std::min(swap_count + 1, 2); // To avoid overflow
			}

		if (to_first_file)
			tmp_fs1 << num << std::endl;
		else
			tmp_fs2 << num << std::endl;

		prev_num = num;
	}

	return swap_count > 1;
}

template <typename T>
void ExternalSort<T>::natural_merge_step(
		std::ofstream &out_fs,
		std::ifstream &tmp_fs1,
		std::ifstream &tmp_fs2)
{
	T num1, num2, prev_num1, prev_num2;

	tmp_fs1 >> num1;
	tmp_fs2 >> num2;

	while (tmp_fs1.good() && tmp_fs2.good()) {
		if (num2 < num1) {
			out_fs << num2 << std::endl;
			prev_num2 = num2;
			tmp_fs2 >> num2;

			if (num2 < prev_num2)
				num1 = sync_sequences(tmp_fs1, out_fs, num1);
		} else {
			out_fs << num1 << std::endl;
			prev_num1 = num1;
			tmp_fs1 >> num1;

			if (num1 < prev_num1)
				num2 = sync_sequences(tmp_fs2, out_fs, num2);
		}
	}

	finish_sequences(tmp_fs1, out_fs, num1);
	finish_sequences(tmp_fs2, out_fs, num2);
}

template <typename T>
void ExternalSort<T>::natural_sort() {
	bool first_iteration = true, continue_iterate = true;

	while (continue_iterate) {
		std::ifstream iinp_fs, itmp_fs1, itmp_fs2;
		std::ofstream oinp_fs, otmp_fs1, otmp_fs2;

		// split section
		otmp_fs1.open(tmp1_file.c_str());
		otmp_fs2.open(tmp2_file.c_str());

		if (first_iteration) {
			iinp_fs.open(inp_file.c_str());
			first_iteration = false;
		} else
			iinp_fs.open(out_file.c_str());

		continue_iterate = natural_split_step(iinp_fs, otmp_fs1, otmp_fs2);

		iinp_fs.close();
		otmp_fs1.close();
		otmp_fs2.close();

		// merge section
		oinp_fs.open(out_file.c_str());
		itmp_fs1.open(tmp1_file.c_str());
		itmp_fs2.open(tmp2_file.c_str());

		natural_merge_step(oinp_fs, itmp_fs1, itmp_fs2);

		oinp_fs.close();
		itmp_fs1.close();
		itmp_fs2.close();
	}
}
