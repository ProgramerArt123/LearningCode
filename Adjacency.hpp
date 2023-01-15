#ifndef __CODE_LEARNING_ADJACENCY_HPP__
#define __CODE_LEARNING_ADJACENCY_HPP__

#include <string>
#include "LexisType.h"
namespace code_learning {

	class Glob;

	template<typename Base, typename Element>
	class Adjacency {
	public:
		Adjacency(const std::string &content, Glob &glob) :
			m_element(new Element(content, glob)) {
		}
		Adjacency &operator++(int) {
			m_count++;
			return *this;
		}
		uint64_t GetCount()const {
			return m_count;
		}
		std::shared_ptr<Base> m_element;
	protected:
		uint64_t m_count = 0;
	};

}

#endif