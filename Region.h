#ifndef __CODE_LEARNING_REGION_H__
#define __CODE_LEARNING_REGION_H__

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
		class Region : public Element {
		public:
			explicit Region(const std::string &content, Config &cfg);
			void Statistics(code::Region &region);
			void Summary()const override;
		private:
			ListMap<Frequency<statistics::Line>> m_lines;
		};
	}
}

#endif