#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "long_num.h"
#include "external_sort.h"

using namespace std;

inline char separator() {
#ifdef _WIN32
	return '\\';
#else
	return '/';
#endif
}

string get_temp_path() {
	const char* temp = getenv("XDG_RUNTIME_DIR");
	temp = temp ? temp : getenv("TMPDIR");
	temp = temp ? temp : getenv("TMP");
	temp = temp ? temp : getenv("TEMP");

#ifdef _WIN32
	temp = temp ? temp : ".";
#else
	temp = temp ? temp : "/tmp";
#endif

#ifdef DEBUG
	temp = ".";
#endif

	string temp_path(temp);
	if (temp_path[temp_path.length() - 1] != separator())
		temp_path = temp_path + separator();

	return temp_path;
}

const string
	INPUT_FILE = "input.txt",
	OUTPUT_FILE = "output.txt",
	TMP_FOLDER = get_temp_path(); // with separator at the end

int main() {
	srand((unsigned) time(NULL));

	clock_t start = clock();

	ExternalSort<LongNum> sorting(INPUT_FILE, OUTPUT_FILE, TMP_FOLDER);
	sorting.natural_sort();

	clock_t end = clock();

	double seconds = (double)(end - start) / CLOCKS_PER_SEC;

	printf("Elapsed time: %g sec.\n", seconds);

	return 0;
}
