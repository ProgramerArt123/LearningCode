#ifndef __CODE_LEARNING_ALGORITHM_FRACTION_H__
#define __CODE_LEARNING_ALGORITHM_FRACTION_H__

#include <cstdint>
#include "Number.h"
#include "Integer.h"

namespace code_learning {

	namespace algorithm {

		class Fraction : public Number {
		public :
			Fraction(int64_t value = 0);
			Fraction(const Integer &integer);
			Fraction(const Integer &numerator, const Integer &denominator);
			const std::string GetString() override;

			Fraction &SetDecimal(bool isDecimal);

			bool IsPositive() const;
			Fraction operator-() const;
			bool operator<(const Fraction &other) const;
			bool operator==(const Fraction &other) const;

			Fraction operator+(const Fraction &addition) const;
			Fraction operator-(const Fraction &subtrahend) const;
			Fraction operator*(const Fraction &multiplier) const;
			Fraction operator/(const Fraction &divisor) const;

			Fraction &operator+=(const Fraction &addition);
			Fraction &operator*=(const Fraction &multiplier);

			friend bool operator==(int number, const Fraction &rational);
			friend Fraction operator-(int number, const Fraction &rational);

			Integer m_numerator = 0;
			Integer m_denominator = UINT64_MAX;
			bool m_is_decimal = false;
		};

	}

}

#endif