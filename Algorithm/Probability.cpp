#include <cassert>
#include "Probability.h"
namespace code_learning {

	namespace algorithm {
		
		Probability::Probability() :
			m_part(0, m_all) {

		}
		Probability::Probability(uint64_t part, uint64_t all) :
			m_all(all), m_part(part, m_all) {
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