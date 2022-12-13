#ifndef __CODE_LEARNING_ADJACENCY_WORD_H__
#define __CODE_LEARNING_ADJACENCY_WORD_H__

#include <string>
#include "WordType.h"

namespace code_learning {

	struct Config;

	class AdjacencyWord {
	public:
		explicit AdjacencyWord(const std::string &content, const Config &cfg);
		AdjacencyWord &operator++(int);
		const std::string &GetContent()const;
		uint64_t GetCount()const;
		WORD_TYPE GetType() const;
		virtual void Sort();
		static WORD_TYPE JudgeWordType(const std::string &content);
	protected:
		const std::string m_content;
		uint64_t m_count = 0;
		WORD_TYPE m_type = WORD_TYPE_NONE;
	};

}

#endif