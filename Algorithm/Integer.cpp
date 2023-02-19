
#include "Integer.h"
namespace code_learning {

	namespace algorithm {
		Integer::Integer(uint64_t value, bool positive):
			m_value(value), m_positive(positive){

		}
		Integer::operator bool() const {
			return m_value;
		}
		Integer Integer::operator%(const Integer &other) const {
			Integer remainder = m_value % other.m_value;
			remainder.m_positive = m_positive == other.m_positive;
			return remainder;
		}
		Integer Integer::GreatestCommonDivisor(const Integer &a, const Integer &b) {
			return b ? GreatestCommonDivisor(b, a%b) : a;
		}

	}

}