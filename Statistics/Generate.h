#ifndef __CODE_LEARNING_STATISTICS_GENERATE_H__
#define __CODE_LEARNING_STATISTICS_GENERATE_H__

#include <set>
#include <map>
#include <iostream>
#include "Code/Char.h"

namespace code_learning {
	namespace statistics {
		class Wrapper {
		public:
			explicit Wrapper() {
			}
			explicit Wrapper(const std::string &prefix) :
				m_prefix(prefix) {
			}
			explicit Wrapper(const std::string &prefix, const std::string &suffix) :
				m_prefix(prefix), m_suffix(suffix) {
			}
			bool operator<(const Wrapper &other) const {
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
			Wrapper &operator=(const Wrapper &other) {
				m_prefix = other.m_prefix;
				return *this;
			}
			std::string m_prefix;
			std::string m_suffix;
		};

		class Generate {
		public:
			std::set<Wrapper> wrappers;
			std::map<char, code::Symmetry> symmetries;
			void Summary()const {
				if (!symmetries.empty()) {
					std::cout << "#################################################" << std::endl;
					std::cout << "Symmetries:" << std::endl;
					for (auto &symmetry : symmetries) {
						std::cout << symmetry.second.m_left << ":" << symmetry.second.m_right << std::endl;
					}
				}
			}
		};
	}
}

#endif