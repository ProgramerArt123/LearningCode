#ifndef __CODE_LEARNING_FREQUENCY_HPP__
#define __CODE_LEARNING_FREQUENCY_HPP__

#include "Adjacency.hpp"
#include "Adjacencies.hpp"

namespace code_learning {

	class Glob;

	template<typename Base, typename Element>
	class Frequency : public Adjacency<Base, Element> {
	public:
		Frequency(const std::string &content, Glob &glob) :
			Adjacency<Base, Element>(content, glob), m_front(glob), m_back(glob) {

		}
		void Sort() {
			m_front.Sort();
			m_back.Sort();
		}
		void Summary()const {
			Adjacency<Base, Element>::m_element->Summary();
		}
		Adjacencies<Base, Element> m_front;
		Adjacencies<Base, Element> m_back;
	};
}

#endif