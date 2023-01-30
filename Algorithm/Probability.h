#ifndef __CODE_LEARNING_ALGORITHM_PROBABILITY_H__
#define __CODE_LEARNING_ALGORITHM_PROBABILITY_H__

#include "Event.h"

namespace code_learning {

	namespace algorithm {

		class Rational {
		public :
			Rational(uint64_t integer, bool positive = true);
			Rational(uint64_t numerator, uint64_t denominator, bool positive = true);
			bool operator==(const Rational &other) const;
			Rational operator-(const Rational &other) const;
			static uint64_t GCD(uint64_t a, uint64_t b);
			uint64_t m_numerator = 0;
			uint64_t m_denominator = UINT64_MAX;
			bool m_positive = true;
		};

		class Probability {
		public:
			Probability();
			Probability(uint64_t part, uint64_t all);

			bool operator<(const Probability &other) const;
			bool operator==(const Probability &other) const;
			Rational operator()(const Event &event);

			SampleSpace m_all;
			Event m_part;
		};
	}

}

#endif