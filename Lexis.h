#ifndef __CODE_LEARNING_LEXIS_H__
#define __CODE_LEARNING_LEXIS_H__

#include <list>
#include "Char.h"

namespace code_learning {
	class Lexis {
	public:
		explicit Lexis(char first);
		bool TryAppendChar(char last);
		std::list<char>::const_iterator begin() const;
		std::list<char>::const_iterator end() const;
	private:
		bool IsDisconnection(char last);
	private:
		std::list<char> m_content;
		CHAR_TYPE m_last = CHAR_TYPE_NONE;
	};
}

#endif