#include "Probability.h"
#include "IndependentEvent.h"

namespace code_learning {

	namespace algorithm {
		IndependentEvent::IndependentEvent(uint64_t count, const SampleSpace &space):
			Event(count, space){

		}
		IndependentEvent IndependentEvent::operator&(const IndependentEvent &other)const {
			IndependentEvent independent(m_space.m_samples.GetCardinality(), m_space);
			independent.m_independents.insert(dynamic_cast<const IndependentEvent *>(this)); 
			independent.m_independents.insert(dynamic_cast<const IndependentEvent *>(&other));
			return independent;
		}
		Rational IndependentEvent::GetRational() const {
			Rational rational(m_samples.m_samples.GetCardinality(),
				m_space.m_samples.GetCardinality());
			for (const auto &independent : m_independents) {
				rational *= independent->GetRational();
			}
			return rational;
		}
	}

}