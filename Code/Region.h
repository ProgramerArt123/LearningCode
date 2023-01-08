#ifndef __CODE_LEARNING_CODE_REGION_H__
#define __CODE_LEARNING_CODE_REGION_H__

#include <list>
#include <memory>

#include "Code/Line.h"
#include "Code/Block.h"

#include "Composite.hpp"

namespace code_learning {

	class Config;
	namespace statistics {
		class Region;
	}
	namespace code {

		class Lexis;
		class Region : public Composite<code::Line, code::Block, Composite<Lexis, Lexis>> {
		public:
			bool ContentAppend(char c)override;
			std::string GetPattern(const Config &cfg) const override;
			friend class statistics::Region;
		private:
			void ContentAppendBlock(char c);
			bool ContentAppendLine(char c);
			void SetContent();
			int re_line_count = 0;
		};


	}
}

#endif