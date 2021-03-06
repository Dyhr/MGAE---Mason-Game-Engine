#include "Mason/Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string readFileAsString(string filename) {
	ifstream t(filename);
	stringstream buffer;
	buffer << t.rdbuf();
	auto s = buffer.str();
	if (s.length() == 0) {
		cout << "Cannot open file / file is empty : " << filename << endl;
	}
	return s;
}