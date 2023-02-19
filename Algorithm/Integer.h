#ifndef __CODE_LEARNING_ALGORITHM_INTEGER_H__
#define __CODE_LEARNING_ALGORITHM_INTEGER_H__

#include <cstdint>

namespace code_learning {

	namespace algorithm {

		class Integer {
		public :
			Integer(uint64_t value, bool positive = true);
			static Integer GreatestCommonDivisor(const Integer &a, const Integer &b);
			operator bool() const;
			Integer operator%(const Integer &other) const;
			uint64_t m_value = 0;
			bool m_positive = true;
		};

	}

}

#endif