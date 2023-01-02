#ifndef __CODE_LEARNING_GENERATE_H__
#define __CODE_LEARNING_GENERATE_H__

#include <set>
#include <map>

namespace code_learning {
	
	class Wrapper {
	public:
		explicit Wrapper(){
		}
		explicit Wrapper(const std::string &prefix) :
			m_prefix(prefix) {
		}
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
		Wrapper &operator=(const Wrapper &other){
			m_prefix = other.m_prefix;
			return *this;
		}
		std::string m_prefix;
		std::string m_suffix;
	};

	class Symmetry {
	public:
		explicit Symmetry(char left, char right) :
			m_left(left), m_right(right) {
		}
		bool operator<(const Symmetry &other) const {
			if (m_left < other.m_left) {
				return true;
			}
			if (m_left > other.m_left) {
				return false;
			}
			if (m_right < other.m_right) {
				return true;
			}
			if (m_right > other.m_right) {
				return false;
			}
			return false;
		}
		char m_left;
		char m_right;
	};
	
	class Generate {
	public:
		std::set<Wrapper> wrappers;
		std::map<char, Symmetry> symmetries;
	};
}

#endif