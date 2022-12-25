#ifndef __CODE_LEARNING_LINE_H__
#define __CODE_LEARNING_LINE_H__

#include "Word.h"
#include "Adjacencies.hpp"
#include "ListMap.hpp"
#include "Element.h"

namespace code_learning {
	class Line : public Element {
	public:
		explicit Line(const std::string &content, const Config &cfg);
		void AppendWord(const std::string &content);
	private:
		ListMap<Word> m_adjacencies;
	};
}

#endif