#ifndef __CODE_LEARNING_CODE_LEXIS_H__
#define __CODE_LEARNING_CODE_LEXIS_H__

#include <list>
#include "Char.h"
#include "Element.h"
#include "LexisType.h"

namespace code_learning {

	class Glob;

	namespace code {
		class Lexis : public Element{
		public:
			Lexis();
			explicit Lexis(char first);
			bool TryAppendChar(char next, const Glob &glob) override;
			bool ContentAppend(char next, const Glob &glob) override;
			std::string GetPattern() const override;
			bool IsMulti()const override;
			bool IsSpace()const override;
			bool IsNewLine()const;
		private:
			bool IsDisconnection(char next);
		private:
			CHAR_TYPE m_last = CHAR_TYPE_NONE;
		};
	}
}

#endif