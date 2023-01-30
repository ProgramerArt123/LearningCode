#include "Event.h"

namespace code_learning {
	namespace algorithm {
		Event::Event(const SampleSpace &space):m_space(space){
			m_type = EVENT_TYPE_CERTAIN;
			m_samples = m_space.m_samples;
		}
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
			return *this;
		}

		Event &Event::operator-=(const Event &other) {
			for (const auto &range : other.m_samples.m_ranges) {
				m_samples.Difference(range);
			}
			if (0 == m_samples.GetCardinality()) {
				m_type = EVENT_TYPE_IMPOSSIBLE;
			}
			else if (m_samples.GetCardinality() < m_space.m_samples.GetCardinality()) {
				m_type = EVENT_TYPE_POSSIBLE;
			}
			return *this;
		}

		Event Event::operator!()const {
			Event complement(m_space);
			complement -= *this;
			return complement;
		}

	}
}