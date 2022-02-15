#include <string>
#include <algorithm> 
#include <cctype>
#include <locale>

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

	}

}