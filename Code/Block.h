#ifndef __CODE_LEARNING_CODE_BLOCK_H__
#define __CODE_LEARNING_CODE_BLOCK_H__

#include <list>
#include <memory>
#include "Element.h"
#include "Composite.hpp"

namespace code_learning {
	class Config;

	namespace code {

		class Lexis;

		class Block : public Composite<code::Element>{
		public:
			explicit Block(char first);
			ELEMENT_TYPE GetType() const override;
			void Decomposition(const Glob &glob) override;
			bool TryAppendChar(char next, const Glob &glob) override;
			bool ContentAppend(char next, const Glob &glob)override;
			std::string GetPattern(const Glob &glob) const override;
		private:
			bool CheckEncoding(const char *content, size_t &index, const Glob &glob);
			const char m_wrapper = ' ';
		};

	}
}

#endif