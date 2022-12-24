#ifndef __CODE_LEARNING_FREQUENCY_WORD_H__
#define __CODE_LEARNING_FREQUENCY_WORD_H__

#include "AdjacencyWord.h"
#include "AdjacencyWords.h"

namespace code_learning {

	class Config;

	class FrequencyWord : public AdjacencyWord {
	public:
		explicit FrequencyWord(const std::string &content, const Config &cfg);
		void Sort() override;
		AdjacencyWords m_front;
		AdjacencyWords m_back;
	};
}

#endif