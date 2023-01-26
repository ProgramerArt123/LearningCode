#ifndef __CODE_LEARNING_STATISTICS_PATH_H__
#define __CODE_LEARNING_STATISTICS_PATH_H__

#include "File.h"

namespace code_learning {
	namespace statistics {
		class Path : public File {
		public:
			explicit Path(const std::string &content, Glob &glob);
			void Statistics(const code::Element &element) override;
		};
	}
}

#endif