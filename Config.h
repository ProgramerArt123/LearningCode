#ifndef __CODE_LEARNING_CONFIG_H__
#define __CODE_LEARNING_CONFIG_H__

#include <set>

namespace code_learning {
	
	class Wrapper {
	public:
		explicit Wrapper(const std::string &prefix, const std::string &suffix):
			m_prefix(prefix), m_suffix(suffix){
		}
		bool operator<(const Wrapper &other) const{
			if (m_prefix < other.m_prefix) {
				return true;
			}
			if (m_prefix > other.m_prefix) {
				return false;
			}
			if (m_suffix < other.m_suffix) {
				return true;
			}
			if (m_suffix > other.m_suffix) {
				return false;
			}
			return false;
		}
		std::string m_prefix;
		std::string m_suffix;
	};
	
	class Config {
	public:
		std::set<char> ignores;
		std::set<char> splits;
		std::set<Wrapper> wrappers;
	};
}

#endif