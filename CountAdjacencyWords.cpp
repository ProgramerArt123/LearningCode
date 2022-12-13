#include <iostream>
#include "CountAdjacencyWords.h"

namespace code_learning {
	CountAdjacencyWords::CountAdjacencyWords(WORD_TYPE type, const Config &cfg):
		m_type(type), m_adjacencies(cfg){

	}
	CountAdjacencyWords::CountAdjacencyWords(const CountAdjacencyWords& other) :
		m_type(other.m_type), m_adjacencies(other.m_adjacencies.m_cfg) {
	}
}