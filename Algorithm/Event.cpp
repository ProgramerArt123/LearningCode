#include <cassert>
#include "Probability.h"
#include "Event.h"

namespace code_learning {
	namespace algorithm {
		Event::Event() : SampleSpace(1), m_space(*this) {
			m_type = EVENT_TYPE_CERTAIN;
		}
		Event::Event(const Event &prototype) :
			m_space(&prototype.m_space!=&prototype?prototype.m_space:*this) {
			*this = prototype;
		}
		Event::Event(const SampleSpace &space):m_space(space){
			m_type = EVENT_TYPE_CERTAIN;
			m_samples = m_space.m_samples;
		}
		Event::Event(const Event &prototype, const SampleSpace &space) : m_space(space) {
			*this = prototype;
			SetType();
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
			m_independents = prototype.m_independents;
			return *this;
		}

		Event Event::operator-(const Event &other) const{
			assert(&m_space == &other.m_space);
			Event difference(*this);
			difference.m_samples -= other.m_samples;
			difference.SetType();
			return difference;
		}

		Event Event::operator+(const Event &other) const {
			assert(&m_space == &other.m_space);
			Event unions(*this);
			unions.m_samples += other.m_samples;
			unions.SetType();
			return unions;
		}

		Event &Event::operator-=(const Event &other) {
			return *this = *this - other;
		}

		Event Event::operator&(const Event &other)const {
			if (&m_space == &other.m_space) {
				return *this - (*this - other);
			}
			else {
				Event independent;
				independent.m_independents.insert(dynamic_cast<const Event *>(this));
				independent.m_independents.insert(dynamic_cast<const Event *>(&other));
				return independent;
			}
		}

		Event Event::operator|(const Event &other) const {
			assert(&m_space == &other.m_space);
			return Event(*this&other, other);
		}

		Event Event::operator!()const {
			return Event(m_space) - *this;
		}
		
		Rational Event::GetRational() const {
			Rational rational(m_samples.GetCardinality(),
				m_space.m_samples.GetCardinality());
			for (const auto &independent : m_independents) {
				rational *= independent->GetRational();
			}
			return rational;
		}
	}
}