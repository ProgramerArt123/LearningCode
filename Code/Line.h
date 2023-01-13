#ifndef __CODE_LEARNING_CODE_LINE_H__
#define __CODE_LEARNING_CODE_LINE_H__

#include <list>
#include <memory>
#include "Composite.hpp"

namespace code_learning {

	class Config;

	namespace code {

		class Lexis;

		class Line : public Composite<code::Lexis, code::Lexis>{
		public:
			ELEMENT_TYPE GetType() const override;
			void Decomposition(const Glob &glob) override;
			bool ContentAppend(char next, const Glob &glob)override;
			std::string GetPattern(const Glob &glob) const override;
		private:
			bool CheckEncoding(const char *content, size_t &index, const Glob &glob);
		};

	}
}

#endif