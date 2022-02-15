#include<iostream>
#include<fstream>

using namespace std;

namespace Gecko {
	
	string readfile(const char* inputFile) {
		ifstream in_file(inputFile);
		string out = "";
		char c;

		while (in_file.get(c)) {
			out += c;
		}

		if (out.substr(0, 3) == "\xEF\xBB\xBF") out = out.substr(3);

		return out;
	}

}