#ifndef __CODE_LEARNING_STATISTICS_DESCRIPTION_H__
#define __CODE_LEARNING_STATISTICS_DESCRIPTION_H__

#include "CountAdjacencies.hpp"

namespace code_learning {

	class Glob;
	namespace statistics {
		class Description {
		public:
			explicit Description(const std::string &content);

			const std::string m_content;
			std::string m_front;
			std::string m_back;
		};
	}
}

#endif