#ifndef __CODE_LEARNING_STATISTICS_FILE_H__
#define __CODE_LEARNING_STATISTICS_FILE_H__

#include "Code.h"

namespace code_learning {
	namespace statistics {
		class File : public Code {
		public:
			explicit File(const std::string &content, Glob &glob);
			void Statistics(const code::Element &element) override;
		};
	}
}

#endif