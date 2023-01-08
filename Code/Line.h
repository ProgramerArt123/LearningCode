#ifndef __CODE_LEARNING_CODE_LINE_H__
#define __CODE_LEARNING_CODE_LINE_H__

#include <list>
#include <memory>
#include "Composite.hpp"

namespace code_learning {

	class Config;

	namespace code {

		class Lexis;
		class Line : public Composite<Lexis, Lexis>{
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