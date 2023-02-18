#include <cassert>
#include "Probability.h"
#include "Event.h"

namespace code_learning {
	namespace algorithm {
		Event::Event(uint64_t count) : SampleSpace(count), m_space(*this) {
			if (count) {
				m_type = EVENT_TYPE_CERTAIN;
			}
			else {
				m_type = EVENT_TYPE_IMPOSSIBLE;
			}
		}
		Event::Event(const Event &prototype) :
			m_space(&prototype.m_space != &prototype ? prototype.m_space : *this){
			*this = prototype;
		}
		Event::Event(const SampleSpace &space) : m_space(space) {
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
		Event::Event(const Event &independentA, const Event &independentB,
			std::function<void(Event &, const Event &)> update,
			std::function<Event(const Event &)> insert) :
			Event(1) {
			independentA.GetIndependents(m_independents, update);
			independentB.GetIndependents(m_independents, update, insert);
			m_independent_type = INDEPENDENT_TYPE_AND;
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
			m_independent_type = prototype.m_independent_type;
			return *this;
		}

		Event Event::operator-(const Event &other) const {
			if (&m_space == &other.m_space) {
				if (m_independents.empty()) {
					Event difference(*this);
					difference.m_samples -= other.m_samples;
					difference.SetType();
					return difference;
				}
				else {
					return Event(0);
				}
			}
			else {
				return Event(*this, other, 
					[](Event &one, const Event &other) {
					one.m_samples -= other.m_samples;
					one.SetType();
				},
					[](const Event &other) {
					return !other;
				});
			}
		}

		Event Event::operator+(const Event &other) const {
			if (&m_space == &other.m_space) {
				if (m_independents.empty()) {
					Event unions(*this);
					unions.m_samples += other.m_samples;
					unions.SetType();
					return unions;
				}
				else {
					return *this;
				}
			}
			else {
				return Event(*this, other,
					[](Event &one, const Event &other) {
					one.m_samples += other.m_samples;
					one.SetType();
				},
					[](const Event &other) {
					return other;
				});
			}
		}

		Event &Event::operator-=(const Event &other) {
			return *this = *this - other;
		}

		Event Event::operator&(const Event &other)const {
			if (&m_space == &other.m_space) {
				if (m_independents.empty()) {
					return *this - (*this - other);
				}
				else {
					return *this;
				}
			}
			else {
				return Event(*this, other, 
					[](Event &one, const Event &other) {
					one = one - (one - other);
				},
					[](const Event &other) {
					return other;
				});
			}
		}

		Event Event::operator|(const Event &other) const {
			assert(&m_space == &other.m_space);
			return Event(*this&other, static_cast<const SampleSpace &>(other));
		}

		Event Event::operator!()const {
			if (m_independents.empty()) {
				return Event(m_space) - *this;
			}
			else {
				Event complement(*this);
				complement.m_independent_type = INDEPENDENT_TYPE_OR;
				for (auto &independent : complement.m_independents) {
					independent.second = Event(independent.second.m_space) - independent.second;
				}
				return complement;
			}
		}

		Rational Event::GetRational() const {
			if (0 == m_samples.GetCardinality()) {
				return Rational(0, UINT64_MAX);
			}
			switch (m_independent_type)
			{
			case INDEPENDENT_TYPE_AND:
			{
				Rational rational(1);
				for (const auto &independent : m_independents) {
					rational *= independent.second.GetRational();
				}
				return rational;
			}
				break;
			case INDEPENDENT_TYPE_OR:
			{
				Rational rational(1);
				for (const auto &independent : m_independents) {
					rational *= (!independent.second).GetRational();
				}
				return 1 - rational;
			}
				break;
			default:
				return Rational(m_samples.GetCardinality(),
					m_space.m_samples.GetCardinality());
				break;
			}
		}

		void Event::GetIndependents(std::map<const SampleSpace *, Event> &wrapper,
			std::function<void(Event &, const Event &)> update,
			std::function<Event(const Event &)> insert) const {
			if (m_independents.empty()) {
				GetIndependent(wrapper, &m_space, *this, update, insert);
			}
			else {
				for (const auto &independent : m_independents) {
					GetIndependent(wrapper, independent.first, independent.second, update, insert);
				}
			}
		}

		void Event::GetIndependent(std::map<const SampleSpace *, Event> &wrapper,
			const SampleSpace *space, const Event &event,
			std::function<void(Event &, const Event &)> update,
			std::function<Event(const Event &)> insert) const {
			if (wrapper.find(space) == wrapper.end()) {
				wrapper.insert(std::make_pair(space, insert(event)));
			}
			else {
				update(wrapper.at(space), event);
			}
		}

		bool Event::IsSameIndependentSamples(const Event &other) const {
			if (m_independents.empty() || other.m_independents.empty()) {
				return false;
			}
			if (m_independents.size() != other.m_independents.size()) {
				return false;
			}
			for (const auto &independent : m_independents) {
				if (other.m_independents.find(independent.first) ==
					other.m_independents.end()) {
					return false;
				}
			}
			return true;
		}
	}
}