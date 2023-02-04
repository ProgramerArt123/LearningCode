#include <cassert>
#include "Probability.h"
#include "IndependentEvent.h"

namespace code_learning {

	namespace algorithm {
		IndependentEvent::IndependentEvent():
			Event(1, *this){

		}
		IndependentEvent::IndependentEvent(uint64_t count, const SampleSpace &space) :
			Event(count, space) {

		}
		IndependentEvent IndependentEvent::operator&(const IndependentEvent &other)const {
			assert(&m_space!=&other.m_space);
			IndependentEvent independent;
			independent.m_independents.insert(dynamic_cast<const IndependentEvent *>(this)); 
			independent.m_independents.insert(dynamic_cast<const IndependentEvent *>(&other));
			return independent;
		}
		Rational IndependentEvent::GetRational() const {
			Rational rational(1);
			for (const auto &independent : m_independents) {
				rational *= independent->GetRational();
			}
			return rational;
		}
	}

}