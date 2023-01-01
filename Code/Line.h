#ifndef __CODE_LEARNING_CODE_LINE_H__
#define __CODE_LEARNING_CODE_LINE_H__

#include <list>
#include <memory>
#include "Element.hpp"

namespace code_learning {

	class Lexis;
	class Config;

	namespace code {

		class Line : public Element<Lexis>{
		public:
			void Decomposition(const Config &cfg) override;
			bool ContentAppend(char c)override;
			std::string GetPattern(const Config &cfg) const override;
		private:
			bool CheckEncoding(const char *content, size_t &index);
		};

	}
}

#endif