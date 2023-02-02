#include <cassert>
#include "Probability.h"
namespace code_learning {

	namespace algorithm {
		Rational::Rational(uint64_t integer, bool positive) :
			m_numerator(integer), m_denominator(1), m_positive(positive) {
		}
		Rational::Rational(uint64_t numerator, uint64_t denominator, bool positive):
			m_numerator(numerator), m_denominator(denominator), m_positive(positive){
			assert(m_denominator);
			uint64_t common = GCD(m_numerator, m_denominator);
			m_numerator /= common;
			m_denominator /= common;
		}
		Rational Rational::operator-() const {
			return Rational(m_numerator, m_denominator, !m_positive);
		}
		bool Rational::operator<(const Rational &other) const {
			if (0 == m_numerator == other.m_numerator) {
				return false;
			}
			if (m_positive && !other.m_positive) {
				return false;
			}
			if (!m_positive && other.m_positive) {
				return true;
			}
			uint64_t common = GCD(m_denominator, other.m_denominator);
			uint64_t selfNumerator = m_numerator * (other.m_denominator / common);
			uint64_t otherNumerator = other.m_numerator * (m_denominator / common);
			return m_positive == (selfNumerator < otherNumerator);
		}
		bool Rational::operator==(const Rational &other) const {
			uint64_t common = GCD(m_denominator, other.m_denominator);
			uint64_t selfNumerator = m_numerator * (other.m_denominator / common);
			uint64_t otherNumerator = other.m_numerator * (m_denominator / common);
			return selfNumerator == otherNumerator && 
				(m_positive == other.m_positive || 0 == selfNumerator);
		}
		Rational Rational::operator+(const Rational &other) const {
			if (m_positive) {
				if (other.m_positive) {
					return PositiveAdd(other);
				}
				else {
					return PositiveSub(other);
				}
			}
			else {
				if (other.m_positive) {
					return other.PositiveSub(*this);
				}
				else {
					return -PositiveAdd(other);
				}
			}
		}
		Rational Rational::operator-(const Rational &other) const {
			if (m_positive) {
				if (other.m_positive) {
					return PositiveSub(other);
				}
				else {
					return PositiveAdd(other);
				}
			}
			else {
				if (other.m_positive) {
					return -PositiveAdd(other);
				}
				else {
					return other.PositiveSub(*this);
				}
			}
		}
		Rational Rational::operator*(const Rational &other) const {
			uint64_t selfNumerator = 0;
			uint64_t otherNumerator = 0;
			uint64_t selfDenominator = UINT64_MAX;
			uint64_t otherDenominator = UINT64_MAX;
			{
				uint64_t common = GCD(m_numerator, other.m_denominator);
				selfNumerator = m_numerator / common;
				otherDenominator = other.m_denominator / common;
			}
			{
				uint64_t common = GCD(m_denominator, other.m_numerator);
				selfDenominator = m_denominator / common;
				otherNumerator = other.m_numerator / common;
			}
			return Rational(selfNumerator * otherNumerator,
				selfDenominator * otherDenominator);
		}
		Rational &Rational::operator*=(const Rational &other) {
			return *this = *this * other;
		}
		Rational Rational::PositiveAdd(const Rational &other) const {
			if (!m_positive || !other.m_positive) {
				throw "sign error";
			}
			uint64_t common = GCD(m_denominator, other.m_denominator);
			uint64_t selfNumerator = m_numerator * (other.m_denominator / common);
			uint64_t otherNumerator = other.m_numerator * (m_denominator / common);
			return Rational(selfNumerator + otherNumerator,
				m_denominator * (other.m_denominator / common));
		}
		Rational Rational::PositiveSub(const Rational &other) const {
			if (!m_positive || !other.m_positive) {
				throw "sign error";
			}
			uint64_t common = GCD(m_denominator, other.m_denominator);
			uint64_t selfNumerator = m_numerator * (other.m_denominator / common);
			uint64_t otherNumerator = other.m_numerator * (m_denominator / common);
			uint64_t numerator = 0;
			bool positive = true;
			if (selfNumerator >= otherNumerator) {
				positive = true;
				numerator = selfNumerator - otherNumerator;
			}
			else {
				positive = false;
				numerator = otherNumerator - selfNumerator;
			}
			return Rational(numerator, m_denominator * (other.m_denominator / common), positive);
		}
		uint64_t Rational::GCD(uint64_t a, uint64_t b) {
			return b ? GCD(b, a%b) : a;
		}
		Probability::Probability() :
			m_part(0, m_all) {

		}
		Probability::Probability(uint64_t part, uint64_t all) :
			m_all(all), m_part(part, m_all) {
			if (EVENT_TYPE_IMPOSSIBLE == m_part.m_type) {
				perror("EVENT_TYPE_IMPOSSIBLE");
			}
		}
		
		bool Probability::operator<(const Probability &other) const {
			return (*this)() < other();
		}
		bool Probability::operator==(const Probability &other) const {
			return (*this)() == other();
		}
		Rational Probability::operator()()const {
			return (*this)(m_part);
		}
		Rational Probability::operator()(const Event &event)const {
			return event.GetRational();
		}
	}

}