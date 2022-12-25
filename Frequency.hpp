#ifndef __CODE_LEARNING_FREQUENCY_HPP__
#define __CODE_LEARNING_FREQUENCY_HPP__

#include "Adjacency.hpp"
#include "Adjacencies.hpp"

namespace code_learning {

	class Config;

	template<typename Element>
	class Frequency : public Adjacency<Element> {
	public:
		Frequency(const std::string &content, const Config &cfg) :
			Adjacency<Element>(content, cfg), m_front(cfg), m_back(cfg) {

		}
		void Sort() {
			m_front.Sort();
			m_back.Sort();
		}
		Adjacencies<Element> m_front;
		Adjacencies<Element> m_back;
	};
}

#endif