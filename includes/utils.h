#ifndef G_UTILS_H
#define G_UTILS_H

#include<vector>
#include<map>

namespace Gecko {
	namespace Utils {
		char* string_to_chr_array(std::string str);
		void ltrim(std::string& s);
		void rtrim(std::string& s);
		void trim(std::string& s);
		std::vector<std::string>* split(std::string s, std::string delimiter);
		void printMap(std::map<std::string, std::string> map);
	}
}

#endif