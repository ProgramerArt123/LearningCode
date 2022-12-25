#ifndef __CODE_LEARNING_COUNT_ADJACENCY_HPP__
#define __CODE_LEARNING_COUNT_ADJACENCY_HPP__

#include "WordType.h"
#include "Adjacency.hpp"
#include "ListMap.hpp"

namespace code_learning {
	
	class Config;

	template<typename Element>
	class CountAdjacency {
	public:
		CountAdjacency(WORD_TYPE type, const Config &cfg) :
			m_type(type), m_adjacencies(cfg) {

		}
		CountAdjacency(const CountAdjacency<Element>& other) :
			m_type(other.m_type), m_adjacencies(other.m_adjacencies.m_cfg) {
		}
		uint64_t m_total_count = 0;
		const WORD_TYPE m_type = WORD_TYPE_NONE;
		ListMap<Adjacency<Element>> m_adjacencies;
	};

}

#endif