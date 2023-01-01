#ifndef __CODE_LEARNING_CODE_REGION_H__
#define __CODE_LEARNING_CODE_REGION_H__

#include <list>
#include <memory>

#include "Code/Line.h"

namespace code_learning {

	class Lexis;
	class Config;
	namespace statistics {
		class Region;
	}
	namespace code {

		class Region : public Element<code::Line> {
		public:
			bool ContentAppend(char c)override;
			std::string GetPattern(const Config &cfg) const override;
			friend class statistics::Region;
		private:
			void SetContent();
			int re_line_count = 0;
		};


	}
}

#endif