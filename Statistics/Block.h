#ifndef __CODE_LEARNING_STATISTICS_BLOCK_H__
#define __CODE_LEARNING_STATISTICS_BLOCK_H__

#include "Config.h"
#include "Generate.h"
#include "Lexis.h"
#include "CountAdjacencies.hpp"
#include "Composite.h"
#include "Code/Lexis.h"
#include "Descriptions.h"
#include "FrequenciesFacade.h"
#include "Line.h"

namespace code_learning {
	namespace code {
		class Block;
	}
	namespace statistics {
		class Block : public Line {
		public:
			explicit Block(const std::string &content, Glob &glob);
			void Statistics(const code::Element &element) override;
		};


	}
}

#endif