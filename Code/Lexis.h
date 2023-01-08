#ifndef __CODE_LEARNING_CODE_LEXIS_H__
#define __CODE_LEARNING_CODE_LEXIS_H__

#include <list>
#include "Char.h"

#include "Element.h"

namespace code_learning {
	namespace code {
		class Lexis : public Element{
		public:
			explicit Lexis();
			explicit Lexis(char first);
			bool TryAppendChar(char next);
			bool ContentAppend(char next) override;
			bool IsMulti()const;
			bool IsSpace()const;
			bool IsNewLine()const;
		private:
			bool IsDisconnection(char next);
		private:
			CHAR_TYPE m_last = CHAR_TYPE_NONE;
		};
	}
}

#endif