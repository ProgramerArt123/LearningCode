#ifndef __CODE_LEARNING_ADJACENCY_HPP__
#define __CODE_LEARNING_ADJACENCY_HPP__

#include <string>
#include "WordType.h"
namespace code_learning {

	class Config;

	template<typename Element>
	class Adjacency {
	public:
		Adjacency(const std::string &content, Config &cfg) :
			m_element(content, cfg) {
		}
		Adjacency &operator++(int) {
			m_count++;
			return *this;
		}
		uint64_t GetCount()const {
			return m_count;
		}
		Element m_element;
	protected:
		uint64_t m_count = 0;
	};

}

#endif