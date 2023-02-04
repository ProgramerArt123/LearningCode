#ifndef __CODE_LEARNING_ALGORITHM_INDEPENDENT_EVENT_H__
#define __CODE_LEARNING_ALGORITHM_INDEPENDENT_EVENT_H__

#include <set>
#include "Event.h"

namespace code_learning {

	namespace algorithm {
		class IndependentEvent : public Event{
		public:
			IndependentEvent();
			IndependentEvent(uint64_t count, const SampleSpace &space);
			IndependentEvent operator&(const IndependentEvent &other)const;
			Rational GetRational() const override;
			std::set<const IndependentEvent *> m_independents;
		};
	}

}

#endif