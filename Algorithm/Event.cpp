#include "Event.h"

namespace code_learning {
	namespace algorithm {
		Event::Event(uint64_t count, const SampleSpace &space) :
			SampleSpace(count), m_space(space) {
			m_is_valid = m_samples.IsSub(m_space.m_samples);
			if (!m_is_valid) {
				m_samples.m_ranges.clear();
				perror("Event invalid!");
			}
		}


		Event Event::operator!()const {
			Event complement = *this;
			complement.m_is_complement = true;
			return complement;
		}
	}
}