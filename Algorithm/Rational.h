#ifndef __CODE_LEARNING_ALGORITHM_RATIONAL_H__
#define __CODE_LEARNING_ALGORITHM_RATIONAL_H__

#include <cstdint>
#include "Number.h"
#include "Integer.h"

namespace code_learning {

	namespace algorithm {

		class Rational : public Number {
		public :
			Rational(int64_t value);
			Rational(const Integer &integer);
			Rational(const Integer &numerator, const Integer &denominator);
			bool IsPositive() const;
			Rational operator-() const;
			bool operator<(const Rational &other) const;
			bool operator==(const Rational &other) const;

			Rational operator+(const Rational &addition) const;
			Rational operator-(const Rational &subtrahend) const;
			Rational operator*(const Rational &multiplier) const;
			Rational operator/(const Rational &divisor) const;

			Rational &operator*=(const Rational &multiplier);

			friend bool operator==(int number, const Rational &rational);
			friend Rational operator-(int number, const Rational &rational);

			Integer m_numerator = 0;
			Integer m_denominator = UINT64_MAX;
		};

	}

}

#endif