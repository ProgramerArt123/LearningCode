#ifndef __CODE_LEARNING_ADJACENCY_WORD_H__
#define __CODE_LEARNING_ADJACENCY_WORD_H__

#include <string>
#include "WordType.h"
#include "Word.h"

namespace code_learning {

	class Config;

	class AdjacencyWord : public Word {
	public:
		explicit AdjacencyWord(const std::string &content, const Config &cfg);
		AdjacencyWord &operator++(int);
		uint64_t GetCount()const;
	protected:
		uint64_t m_count = 0;
	};

}

#endif