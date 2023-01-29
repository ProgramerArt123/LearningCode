#ifndef __CODE_LEARNING_ALGORITHM_PROBABILITY_H__
#define __CODE_LEARNING_ALGORITHM_PROBABILITY_H__

#include "Event.h"

namespace code_learning {

	namespace algorithm {

		class Probability {
		public:
			Probability(uint64_t part, uint64_t all);

			bool operator<(const Probability &other) const;
			
			SampleSpace m_all;
			Event m_part;
		};
	}

}

#endif