#include <cassert>
#include "Integer.h"
#include "Rational.h"
namespace code_learning {

	namespace algorithm {
		Rational::Rational(int64_t value):
			Rational(Integer(value>=0?value:-value, value >= 0)){
		}
		Rational::Rational(const Integer &integer) :
			m_numerator(integer), m_denominator(1) {
		}
		Rational::Rational(const Integer &numerator, const Integer &denominator) :
			m_numerator(numerator), m_denominator(denominator) {
			assert(m_denominator);
			const Integer &common = m_numerator.GreatestCommonDivisor(m_denominator);
			m_numerator /= common;
			m_denominator /= common;
			if (0 == m_numerator) {
				m_denominator.m_positive = true;
			}
		}
		bool Rational::IsPositive() const {
			return m_numerator.m_positive == m_denominator.m_positive;
		}
		Rational Rational::operator-() const {
			return Rational(-m_numerator, m_denominator);
		}
		bool Rational::operator<(const Rational &other) const {
			if (m_numerator.m_positive * m_denominator.m_positive <
				other.m_numerator.m_positive * other.m_denominator.m_positive) {
				return true;
			}
			return m_numerator.m_positive * m_denominator.m_positive ==
				m_numerator * other.m_denominator < other.m_numerator * m_denominator;
		}
		bool Rational::operator==(const Rational &other) const {
			return m_denominator == other.m_denominator &&
				m_numerator == other.m_numerator;
		}
		Rational Rational::operator+(const Rational &addition) const {
			const Integer &common = m_denominator.GreatestCommonDivisor(addition.m_denominator);
			const Integer &selfNumerator = m_numerator * (addition.m_denominator / common);
			const Integer &otherNumerator = addition.m_numerator * (m_denominator / common);
			return Rational(selfNumerator + otherNumerator,
				m_denominator * (addition.m_denominator / common));
		}
		Rational Rational::operator-(const Rational &subtrahend) const {
			return *this + (-subtrahend);
		}
		Rational Rational::operator*(const Rational &multiplier) const {
			Integer selfNumerator = 0;
			Integer otherNumerator = 0;
			Integer selfDenominator = UINT64_MAX;
			Integer otherDenominator = UINT64_MAX;
			{
				const Integer &common = m_numerator.GreatestCommonDivisor(multiplier.m_denominator);
				selfNumerator = m_numerator / common;
				otherDenominator = multiplier.m_denominator / common;
			}
			{
				const Integer &common = m_denominator.GreatestCommonDivisor(multiplier.m_numerator);
				selfDenominator = m_denominator / common;
				otherNumerator = multiplier.m_numerator / common;
			}
			return Rational(selfNumerator * otherNumerator,
				selfDenominator * otherDenominator);
		}
		Rational &Rational::operator*=(const Rational &multiplier) {
			return *this = *this * multiplier;
		}
		Rational Rational::operator/(const Rational &divisor) const {
			assert(divisor.m_numerator);
			return *this * Rational(divisor.m_denominator, divisor.m_numerator);
		}
		bool operator==(int number, const Rational &rational) {
			return Rational(number) == rational;
		}
		Rational operator-(int number, const Rational &rational) {
			return Rational(number) - rational;
		}
	}

}