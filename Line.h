#ifndef __CODE_LEARNING_LINE_H__
#define __CODE_LEARNING_LINE_H__

#include "Word.h"
#include "Words.hpp"

namespace code_learning {
	class Line {
	public:
		void AppendWord(const std::string &content);
	private:
		Words<Word> m_adjacencies;
	};
}

#endif