#ifndef __CODE_LEARNING_STATISTICS_CODE_H__
#define __CODE_LEARNING_STATISTICS_CODE_H__

#include "Region.h"

namespace code_learning {
	namespace statistics {
		class Code : public Region {
		public:
			explicit Code(const std::string &content, Glob &glob);
			void Statistics(const code::Element &element) override;
		private:
			void ProcessSymmetries();
			void ProcessSymmetry(const code::Symmetry &symmetry);
		};
	}
}

#endif