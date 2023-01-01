#ifndef __CODE_LEARNING_ADJACENCIES_HPP__
#define __CODE_LEARNING_ADJACENCIES_HPP__

#include <list>
#include <memory>
#include <string>
#include "CountAdjacency.hpp"

namespace code_learning {
	
	class Config;
	
	template<typename Element>
	class Adjacencies {
	public:
		Adjacencies(Glob &glob) :
			m_glob(glob) {

		}
		CountAdjacency<Element> &operator[](const std::string &content) {
			WORD_TYPE type = Element::JudgeWordType(content);
			for (auto &frequency : m_words) {
				if (frequency->m_type == type) {
					return *frequency;
				}
			}
			m_words.push_back(std::shared_ptr<CountAdjacency<Element>>(new CountAdjacency<Element>(type, m_glob)));
			return *m_words.back();
		}

		Adjacency<Element> &Count(const std::string &content) {
			CountAdjacency<Element> &words = (*this)[content];
			words.m_adjacencies[content]++;
			words.m_total_count++;
			return words.m_adjacencies[content];
		}

		static bool compare(const std::shared_ptr<CountAdjacency<Element>> &one, const std::shared_ptr<CountAdjacency<Element>> &other) {
			return one->m_total_count > other->m_total_count;
		}
		void Sort() {
			for (auto &word : m_words) {
				word->m_adjacencies.Sort();
			}
			m_words.sort(compare);
		}
	private:
		std::list<std::shared_ptr<CountAdjacency<Element>>> m_words;
		Glob &m_glob;
	};

}

#endif