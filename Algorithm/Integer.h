#ifndef __CODE_LEARNING_ALGORITHM_INTEGER_H__
#define __CODE_LEARNING_ALGORITHM_INTEGER_H__

#include <cstdint>
#include "Number.h"

namespace code_learning {

	namespace algorithm {

		class Integer : public Number {
		public :
			Integer(uint64_t value, bool positive = true);
			Integer GreatestCommonDivisor(const Integer &other) const;
			operator bool() const;
			Integer operator-() const;
			Integer operator+(const Integer &addition) const;
			Integer operator-(const Integer &subtrahend) const;
			Integer operator*(const Integer &multiplier) const;
			Integer operator%(const Integer &divisor) const;
			Integer operator/(const Integer &divisor) const;
			Integer &operator/=(const Integer &divisor) ;
			bool operator==(const Integer &other)const;
			uint64_t m_value = 0;
			bool m_positive = true;
		private:
			Integer PositiveAdd(const Integer &addition) const;
			Integer PositiveSub(const Integer &subtrahend) const;

		};

	}

}

#endif