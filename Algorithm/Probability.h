#ifndef __CODE_LEARNING_ALGORITHM_PROBABILITY_H__
#define __CODE_LEARNING_ALGORITHM_PROBABILITY_H__

#include "Event.h"

namespace code_learning {

	namespace algorithm {

		
		class Probability {
		public:
			Probability(uint64_t more, uint64_t all):
				m_more(more), m_all(all) {

			}

			bool operator<(const Probability &other) const{
				return m_more.m_samples.GetSize() * other.m_all.m_samples.GetSize() <
					m_all.m_samples.GetSize() * other.m_more.m_samples.GetSize();
			}

			Event m_more;
			Event m_all;
		};
	}

}

#endif