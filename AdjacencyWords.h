#ifndef __CODE_LEARNING_ADJACENCY_WORDS_H__
#define __CODE_LEARNING_ADJACENCY_WORDS_H__

#include "WordType.h"
#include "AdjacencyWord.h"
#include "FrequencyWords.h"

namespace code_learning {
	
	struct Config;

	class CountAdjacencyWords {
	public:
		explicit CountAdjacencyWords(WORD_TYPE type, const Config &cfg);
		explicit CountAdjacencyWords(const CountAdjacencyWords& other);
		uint64_t m_total_count = 0;
		const WORD_TYPE m_type = WORD_TYPE_NONE;
		FrequencyWords m_frequencies;
	};

	class AdjacencyWords {
	public:
		explicit AdjacencyWords(const Config &cfg);
		CountAdjacencyWords &operator[](const std::string &content);
		AdjacencyWord &Count(const std::string &content);
		void Sort();
	private:
		std::list<CountAdjacencyWords> m_words;
		const Config &m_cfg;
	};

}

#endif