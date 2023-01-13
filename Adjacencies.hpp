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
			LEXIS_TYPE type = Element::JudgeLexisType(content);
			for (auto &frequency : m_lexiss) {
				if (frequency->m_type == type) {
					return *frequency;
				}
			}
			m_lexiss.push_back(std::shared_ptr<CountAdjacency<Element>>(new CountAdjacency<Element>(type, m_glob)));
			return *m_lexiss.back();
		}

		Adjacency<Element> &Count(const std::string &content) {
			CountAdjacency<Element> &lexiss = (*this)[content];
			lexiss.m_adjacencies[content]++;
			lexiss.m_total_count++;
			return lexiss.m_adjacencies[content];
		}

		static bool compare(const std::shared_ptr<CountAdjacency<Element>> &one, const std::shared_ptr<CountAdjacency<Element>> &other) {
			return one->m_total_count > other->m_total_count;
		}
		void Sort() {
			for (auto &lexis : m_lexiss) {
				lexis->m_adjacencies.Sort();
			}
			m_lexiss.sort(compare);
		}
	private:
		std::list<std::shared_ptr<CountAdjacency<Element>>> m_lexiss;
		Glob &m_glob;
	};

}

#endif