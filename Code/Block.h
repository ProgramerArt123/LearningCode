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
		class Block : public Composite<Element, Element>{
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