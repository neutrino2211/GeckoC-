#ifndef G_UTILS_H
#define G_UTILS_H

#include<vector>
#include<map>

template<typename K, typename V>
		std::ostream &operator<<(std::ostream &os,
								const std::map<K, V> &m);
namespace Gecko {
	namespace Utils {
		char* string_to_chr_array(std::string str);
		void ltrim(std::string& s);
		void rtrim(std::string& s);
		void trim(std::string& s);
		std::vector<std::string>* split(std::string s, std::string delimiter);
		template<typename K, typename V> void printMap (std::map<K, V> const& map);
	}
}

#endif