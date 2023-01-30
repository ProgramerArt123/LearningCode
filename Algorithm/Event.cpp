#include "Event.h"

namespace code_learning {
	namespace algorithm {
		Event::Event(uint64_t count, const SampleSpace &space) :
			SampleSpace(count), m_space(space) {
			if (!m_samples.IsSub(m_space.m_samples)) {
				m_samples.m_ranges.clear();
			}
			if (0 == m_samples.GetCardinality()) {
				m_type = EVENT_TYPE_IMPOSSIBLE;
			}
			else if (m_samples.GetCardinality() < m_space.m_samples.GetCardinality()) {
				m_type = EVENT_TYPE_POSSIBLE;
			}
			else {
				m_type = EVENT_TYPE_CERTAIN;
			}
		}

		Event &Event::operator=(const Event &prototype) {
			m_samples = prototype.m_samples;
			m_type = prototype.m_type;
			m_is_complement = prototype.m_is_complement;
			return *this;
		}

		Event Event::operator!()const {
			Event complement = *this;
			complement.m_is_complement = true;
			return complement;
		}

		bool Event::IsComplement() const {
			return m_is_complement;
		}

	}
}