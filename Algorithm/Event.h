#ifndef __CODE_LEARNING_ALGORITHM_EVENT_H__
#define __CODE_LEARNING_ALGORITHM_EVENT_H__

#include "SampleSpace.h"

namespace code_learning {

	namespace algorithm {
		
		class Event : public SampleSpace {
		public:
			Event(uint64_t count, const SampleSpace &space);

			Event operator!()const;

			bool m_is_valid = false;

			const SampleSpace &m_space;
		private:
			bool m_is_complement = false;
		};
	}

}

#endif