#ifndef G_UTILS_H
#define G_UTILS_H

namespace Gecko {
	namespace Utils {
		char* string_to_chr_array(std::string str);
		void ltrim(std::string& s);
		void rtrim(std::string& s);
		void trim(std::string& s);
	}
}

#endif