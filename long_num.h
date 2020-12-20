#pragma once

#include <iostream>
#include <string>

struct LongNum {
private:
	std::string data;
public:
	LongNum() { data = "0"; };
	LongNum(const std::string &str) { data = str; };

	bool operator < (const LongNum &rhn) const {
		if (data.length() == rhn.data.length()) return data < rhn.data;
		return data.length() < rhn.data.length();
	};

	friend std::ostream& operator << (std::ostream &os, const LongNum &num) { return os << num.data; };
	friend std::istream& operator >> (std::istream &is, LongNum &num) { return is >> num.data; };
};
