#ifndef __CODE_LEARNING_ALGORITHM_EVENT_H__
#define __CODE_LEARNING_ALGORITHM_EVENT_H__

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

			void SetType();
			
			Event &operator=(const Event &prototype);

			Event operator-(const Event &other) const;

			Event &operator-=(const Event &other);

			Event operator+(const Event &other) const;

			Event operator&(const Event &other)const;

			Event operator|(const Event &other) const;

			Event operator!()const;

			virtual Rational GetRational() const;

			EVENT_TYPE m_type = EVENT_TYPE_NONE;

			const SampleSpace &m_space;

			std::set<const Event *> m_independents;
		};


	}

}

#endif