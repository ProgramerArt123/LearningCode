#ifndef __CODE_LEARNING_WORD_H__
#define __CODE_LEARNING_WORD_H__

#include "WordType.h"
#include "AdjacencyWord.h"
#include "AdjacencyWords.h"

namespace code_learning {

	struct Config;

	class Word : public AdjacencyWord {
	public:
		explicit Word(const std::string &content, const Config &cfg);
		AdjacencyWords m_front;
		AdjacencyWords m_back;
	};
}

#endif