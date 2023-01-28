#ifndef __CODE_LEARNING_CODE_REGION_H__
#define __CODE_LEARNING_CODE_REGION_H__

#include <list>
#include <memory>

#include "Line.h"

#include "Composite.hpp"

namespace code_learning {

	class Glob;
	namespace statistics {
		class Region;
	}
	namespace code {

		class Lexis;

		class Region : public Composite<code::Line> {
		public:
			explicit Region();
			bool ContentAppend(char next, const Glob &glob)override;
			friend class statistics::Region;
		private:
			bool ContentAppendLine(char next, const Glob &glob);
			void SetContent();
			int re_line_count = 0;
		};


	}
}

#endif