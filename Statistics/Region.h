#ifndef __CODE_LEARNING_STATISTICS_REGION_H__
#define __CODE_LEARNING_STATISTICS_REGION_H__

#include "Line.h"
#include "Adjacencies.hpp"
#include "ListMap.hpp"
#include "Frequency.hpp"
#include "Element.h"

namespace code_learning {
	namespace code {
		class Region;
	};
	namespace statistics {
		class Region : public Composite<statistics::Line>{
		public:
			explicit Region(const std::string &content, Glob &glob);
			void Statistics(code::Region &region);
			void Summary()const override;
		};
	}
}

#endif