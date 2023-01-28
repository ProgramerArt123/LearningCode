#ifndef __CODE_LEARNING_ALGORITHM_EVENT_H__
#define __CODE_LEARNING_ALGORITHM_EVENT_H__

#include "Set.h"

namespace code_learning {

	namespace algorithm {
		
		class Event {
		public:
			explicit Event(uint64_t count):m_samples(count){

			}

			Event operator!() {
				Event complement = *this;
				complement.m_is_complement = true;
				return complement;
			}

			Set m_samples;
		private:
			bool m_is_complement = false;
		};
	}

}

#endif