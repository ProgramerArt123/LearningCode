#ifndef __CODE_LEARNING_FREQUENCY_HPP__
#define __CODE_LEARNING_FREQUENCY_HPP__

#include "Adjacency.hpp"
#include "CountAdjacencies.hpp"

namespace code_learning {

	class Glob;

	template<typename Element>
	class Frequency : public Adjacency<Element> {
	public:
		Frequency(const std::string &content, Glob &glob) :
			Adjacency<Element>(content, glob), m_front(glob), m_back(glob) {

		}
		void Sort() {
			m_front.Sort();
			m_back.Sort();
		}
		void Summary()const {
			Adjacency<Element>::m_element->Summary();
		}
		void FrontCount(const std::string &next) override{
			m_front.Count(next);
		}
		void BackCount(const std::string &pre) override {
			m_back.Count(pre);
		}
		CountAdjacencies<Element> m_front;
		CountAdjacencies<Element> m_back;
	};
}

#endif