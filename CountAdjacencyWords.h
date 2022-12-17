#ifndef __CODE_LEARNING_COUNT_ADJACENCY_WORDS_H__
#define __CODE_LEARNING_COUNT_ADJACENCY_WORDS_H__

#include "WordType.h"
#include "FrequencyWord.h"
#include "Words.hpp"

namespace code_learning {
	
	class Config;

	class CountAdjacencyWords {
	public:
		explicit CountAdjacencyWords(WORD_TYPE type, const Config &cfg);
		explicit CountAdjacencyWords(const CountAdjacencyWords& other);
		uint64_t m_total_count = 0;
		const WORD_TYPE m_type = WORD_TYPE_NONE;
		Words<AdjacencyWord> m_adjacencies;
	};

}

#endif