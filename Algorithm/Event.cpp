#include "Event.h"

namespace code_learning {
	namespace algorithm {
		Event::Event(const Event &prototype) :
			m_space(prototype.m_space) {
			*this = prototype;
		}
		Event::Event(const SampleSpace &space):m_space(space){
			m_type = EVENT_TYPE_CERTAIN;
			m_samples = m_space.m_samples;
		}
		Event::Event(uint64_t count, const SampleSpace &space) :
			SampleSpace(count), m_space(space) {
			if (!m_samples.IsSub(m_space.m_samples)) {
				m_samples.m_ranges.clear();
			}
			SetType();
		}

		void Event::SetType() {
			if (0 == m_samples.GetCardinality()) {
				m_type = EVENT_TYPE_IMPOSSIBLE;
			}
			else if (m_samples.GetCardinality() <
				m_space.m_samples.GetCardinality()) {
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

		Event Event::operator-(const Event &other) const{
			Event difference(*this);
			difference.m_samples -= other.m_samples;
			difference.SetType();
			return difference;
		}

		Event Event::operator+(const Event &other) const {
			Event unions(*this);
			unions.m_samples += other.m_samples;
			unions.m_samples += other.m_samples;
			unions.SetType();
			return unions;
		}

		Event &Event::operator-=(const Event &other) {
			return *this = *this - other;
		}

		Event Event::operator&(const Event &other)const {
			const Event &difference = *this - other;
			return *this - difference;
		}

		Event Event::operator!()const {
			const Event space(m_space);
			return space - *this;
		}

	}
}