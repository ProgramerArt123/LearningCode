#ifndef __CODE_LEARNING_ALGORITHM_RATIONAL_H__
#define __CODE_LEARNING_ALGORITHM_RATIONAL_H__

#include <cstdint>
#include "Integer.h"

namespace code_learning {

	namespace algorithm {

		class Rational {
		public :
			Rational(int64_t value);
			Rational(const Integer &integer);
			Rational(const Integer &numerator, const Integer &denominator);
			bool IsPositive() const;
			Rational operator-() const;
			bool operator<(const Rational &other) const;
			bool operator==(const Rational &other) const;
			Rational operator+(const Rational &other) const;
			Rational operator-(const Rational &other) const;
			Rational operator*(const Rational &other) const;
			Rational &operator*=(const Rational &other);
			Rational operator/(const Rational &other) const;

			friend bool operator==(int number, const Rational &rational);
			friend Rational operator-(int number, const Rational &rational);

			Integer m_numerator = 0;
			Integer m_denominator = UINT64_MAX;
		};

	}

}

#endif