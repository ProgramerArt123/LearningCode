#ifndef __CODE_LEARNING_ALGORITHM_SAMPLE_SPACE_H__
#define __CODE_LEARNING_ALGORITHM_SAMPLE_SPACE_H__

#include "Set.hpp"

namespace code_learning {

	namespace algorithm {
		
		class SampleSpace {
		public:
			explicit SampleSpace(uint64_t count = UINT64_MAX);

			Set m_samples;
		
		};
	}

}

#endif