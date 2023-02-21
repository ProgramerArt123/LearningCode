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
		}
		bool Rational::IsPositive() const {
			return m_numerator.m_positive == m_denominator.m_positive;
		}
		Rational Rational::operator-() const {
			return Rational(-m_numerator, m_denominator);
		}
		bool Rational::operator<(const Rational &other) const {
			const Integer &common = m_denominator.GreatestCommonDivisor(other.m_denominator);
			const Integer &selfNumerator = m_numerator * (other.m_denominator / common);
			const Integer &otherNumerator = other.m_numerator * (m_denominator / common);
			return selfNumerator < otherNumerator;
		}
		bool Rational::operator==(const Rational &other) const {
			const Integer &common = m_denominator.GreatestCommonDivisor(other.m_denominator);
			const Integer &selfNumerator = m_numerator * (other.m_denominator / common);
			const Integer &otherNumerator = other.m_numerator * (m_denominator / common);
			return selfNumerator == otherNumerator;
		}
		Rational Rational::operator+(const Rational &other) const {
			const Integer &common = m_denominator.GreatestCommonDivisor(other.m_denominator);
			const Integer &selfNumerator = m_numerator * (other.m_denominator / common);
			const Integer &otherNumerator = other.m_numerator * (m_denominator / common);
			return Rational(selfNumerator + otherNumerator,
				m_denominator * (other.m_denominator / common));
		}
		Rational Rational::operator-(const Rational &other) const {
			return *this + (-other);
		}
		Rational Rational::operator*(const Rational &other) const {
			Integer selfNumerator = 0;
			Integer otherNumerator = 0;
			Integer selfDenominator = UINT64_MAX;
			Integer otherDenominator = UINT64_MAX;
			{
				const Integer &common = m_numerator.GreatestCommonDivisor(other.m_denominator);
				selfNumerator = m_numerator / common;
				otherDenominator = other.m_denominator / common;
			}
			{
				const Integer &common = m_denominator.GreatestCommonDivisor(other.m_numerator);
				selfDenominator = m_denominator / common;
				otherNumerator = other.m_numerator / common;
			}
			return Rational(selfNumerator * otherNumerator,
				selfDenominator * otherDenominator);
		}
		Rational &Rational::operator*=(const Rational &other) {
			return *this = *this * other;
		}
		Rational Rational::operator/(const Rational &other) const {
			assert(other.m_numerator);
			return *this * Rational(other.m_denominator, other.m_numerator);
		}
		bool operator==(int number, const Rational &rational) {
			return Rational(number) == rational;
		}
		Rational operator-(int number, const Rational &rational) {
			return Rational(number) - rational;
		}
	}

}