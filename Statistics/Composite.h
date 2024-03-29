#ifndef __CODE_LEARNING_STATISTICS_COMPOSITE_H__
#define __CODE_LEARNING_STATISTICS_COMPOSITE_H__

#include <vector>
#include "Element.h"

namespace code_learning {
	namespace statistics {

		class FrequenciesFacade;

		class Composite : public statistics::Element {
		public:
			Composite(const std::string &content, Glob &glob);
			void SetChildrenCount(size_t count);
			void Statistics(const code::Element &element) override;
		protected:
			std::string m_signature;
			std::vector<std::shared_ptr<FrequenciesFacade>> m_children;
		};

	}
}

#endif