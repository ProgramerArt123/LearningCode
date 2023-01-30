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
		}
		bool Rational::operator==(const Rational &other) const {
			uint64_t common = GCD(m_denominator, other.m_denominator);
			uint64_t selfNumerator = m_numerator * (other.m_denominator / common);
			uint64_t otherNumerator = other.m_numerator * (m_denominator / common);
			return selfNumerator == otherNumerator;
		}
		Rational Rational::operator-(const Rational &other) const {
			uint64_t common = GCD(m_denominator, other.m_denominator);
			uint64_t selfNumerator = m_numerator * (other.m_denominator / common);
			uint64_t otherNumerator = other.m_numerator * (m_denominator /common);
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
			return m_part.m_samples.GetCardinality() * other.m_all.m_samples.GetCardinality() <
				m_all.m_samples.GetCardinality() * other.m_part.m_samples.GetCardinality();
		}
		bool Probability::operator==(const Probability &other) const {
			return m_part.m_samples.GetCardinality() * other.m_all.m_samples.GetCardinality() ==
				m_all.m_samples.GetCardinality() * other.m_part.m_samples.GetCardinality();
		}
		Rational Probability::operator()(const Event &event) {
			return Rational(event.m_samples.GetCardinality(),
				event.m_space.m_samples.GetCardinality());
		}
	}

}