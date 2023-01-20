#ifndef __CODE_LEARNING_CODE_REGION_H__
#define __CODE_LEARNING_CODE_REGION_H__

#include <list>
#include <memory>

#include "Line.h"
#include "Block.h"

#include "Composite.hpp"

namespace code_learning {

	class Glob;
	namespace statistics {
		class Region;
	}
	namespace code {

		class Lexis;
		class Region : public Composite<code::Line, code::Block> {
		public:
			ELEMENT_TYPE GetType() const override;
			bool ContentAppend(char next, const Glob &glob)override;
			std::string GetPattern(const Glob &glob) const override;
			friend class statistics::Region;
		private:
			void ContentAppendBlock(char next, const Glob &glob);
			bool ContentAppendLine(char next, const Glob &glob);
			void SetContent();
			int re_line_count = 0;
		};


	}
}

#endif