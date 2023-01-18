#ifndef __CODE_LEARNING_COUNT_ADJACENCY_HPP__
#define __CODE_LEARNING_COUNT_ADJACENCY_HPP__

#include "LexisType.h"
#include "Adjacency.hpp"
#include "ListMap.hpp"

namespace code_learning {
	
	class Glob;

	template<typename Element>
	class CountAdjacency {
	public:
		CountAdjacency(/*LEXIS_TYPE type, */Glob &glob) :
			/*m_type(type), */m_adjacencies(glob) {

		}
		CountAdjacency(const CountAdjacency<Element>& other) :
			/*m_type(other.m_type), */m_adjacencies(other.m_adjacencies.m_cfg) {
		}
		Adjacency<Element> &Get(const std::string &key) {
			return m_adjacencies.Get<Adjacency<Element>>(key);
		}
		uint64_t m_total_count = 0;
		//const LEXIS_TYPE m_type = LEXIS_TYPE_NONE;
		ListMap m_adjacencies;
	};

}

#endif