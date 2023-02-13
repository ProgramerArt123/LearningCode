#ifndef __CODE_LEARNING_ALGORITHM_EVENT_H__
#define __CODE_LEARNING_ALGORITHM_EVENT_H__

#include <map>
#include <functional>

#include "Rational.h"
#include "SampleSpace.h"

namespace code_learning {

	namespace algorithm {
		
		enum EVENT_TYPE
		{
			EVENT_TYPE_NONE,
			EVENT_TYPE_POSSIBLE,
			EVENT_TYPE_CERTAIN,
			EVENT_TYPE_IMPOSSIBLE
		};

		class Event : public SampleSpace{
		public:
			Event();

			Event(const Event &prototype);

			Event(const SampleSpace &space);

			Event(const Event &prototype, const SampleSpace &space);

			Event(uint64_t count, const SampleSpace &space);

			Event(const Event &independentA, const Event &independentB,
				std::function<void(Event &, const Event &)> factor);

			void SetType();
			
			Event &operator=(const Event &prototype);

			Event operator-(const Event &other) const;

			Event &operator-=(const Event &other);

			Event operator+(const Event &other) const;

			Event operator&(const Event &other)const;

			Event operator|(const Event &other) const;

			Event operator!()const;

			virtual Rational GetRational() const;

			void GetIndependents(std::map<const SampleSpace *, Event> &wrapper, 
				std::function<void(Event &, const Event &)> factor) const;

			void GetIndependent(std::map<const SampleSpace *, Event> &wrapper, 
				const SampleSpace *space, const Event &event,
				std::function<void(Event &, const Event &)> factor) const;

			bool IsSameIndependentSamples(const Event &other) const;

			EVENT_TYPE m_type = EVENT_TYPE_NONE;

			const SampleSpace &m_space;

			std::map<const SampleSpace *, Event> m_independents;
		};


	}

}

#endif