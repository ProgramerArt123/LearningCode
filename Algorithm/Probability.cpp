#include "Probability.h"

namespace code_learning {

	namespace algorithm {
		Probability::Probability(uint64_t part, uint64_t all) :
			m_all(all), m_part(part, m_all) {
			m_part.m_samples.AddRanges(Range(0, 0), Range(0, 0));
		}

		bool Probability::operator<(const Probability &other) const {
			return m_part.m_samples.GetSize() * other.m_all.m_samples.GetSize() <
				m_all.m_samples.GetSize() * other.m_part.m_samples.GetSize();
		}
	}

}