#ifndef __CODE_LEARNING_ALGORITHM_PROBABILITY_H__
#define __CODE_LEARNING_ALGORITHM_PROBABILITY_H__

#include "Event.h"

namespace code_learning {

	namespace algorithm {

		class Probability {
		public:
			Probability();
			Probability(uint64_t part, uint64_t all);

			bool operator<(const Probability &other) const;
			bool operator==(const Probability &other) const;
			Rational operator()()const;
			Rational operator()(const Event &event)const;

			SampleSpace m_all;
			Event m_part;
		};
	}

}

#endif