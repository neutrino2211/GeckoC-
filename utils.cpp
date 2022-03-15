#include <string>
#include <algorithm> 
#include <cctype>
#include <locale>
#include "includes/utils.h"

using namespace std;

namespace Gecko {

	namespace Utils {

		char* string_to_chr_array(string str) {
			char* writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0'; // don't forget the terminating 0

			return writable;
		}


		// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
		void ltrim(std::string& s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
				return !std::isspace(ch);
			}));
		}

		// trim from end (in place)
		void rtrim(std::string& s) {
			s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
				return !std::isspace(ch);
			}).base(), s.end());
		}

		// trim from both ends (in place)
		void trim(std::string& s) {
			ltrim(s);
			rtrim(s);
		}

		std::vector<std::string>* split(std::string s, std::string delimiter) {
			std::vector<std::string>* r = new std::vector<std::string>;
			size_t pos = 0;
			std::string token;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				r->push_back(token);
				s.erase(0, pos + delimiter.length());
			}
			r->push_back(s);
			return r;
		}

		void printMap (std::map<std::string, std::string> map) {
			printf("{\n");
			for(const auto& elem : map) {
				printf("\"%s\": \"%s\",\n", elem.first.c_str(), elem.second.c_str());
			}
			printf("}");
			return;
		}

	}

}