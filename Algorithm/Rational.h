#ifndef __CODE_LEARNING_ALGORITHM_RATIONAL_H__
#define __CODE_LEARNING_ALGORITHM_RATIONAL_H__

#include <cstdint>

namespace code_learning {

	namespace algorithm {

		class Rational {
		public :
			Rational(uint64_t integer, bool positive = true);
			Rational(uint64_t numerator, uint64_t denominator, bool positive = true);
			Rational operator-() const;
			bool operator<(const Rational &other) const;
			bool operator==(const Rational &other) const;
			Rational operator+(const Rational &other) const;
			Rational operator-(const Rational &other) const;
			Rational operator*(const Rational &other) const;
			Rational &operator*=(const Rational &other);
			Rational operator/(const Rational &other) const;
			Rational PositiveAdd(const Rational &other) const;
			Rational PositiveSub(const Rational &other) const;

			friend bool operator==(int number, const Rational &rational);
			friend Rational operator-(int number, const Rational &rational);

			static uint64_t GCD(uint64_t a, uint64_t b);
			uint64_t m_numerator = 0;
			uint64_t m_denominator = UINT64_MAX;
			bool m_positive = true;
		};

	}

}

#endif