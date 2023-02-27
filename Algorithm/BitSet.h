#ifndef __CODE_LEARNING_ALGORITHM_BIT_SET_H__
#define __CODE_LEARNING_ALGORITHM_BIT_SET_H__

#include <cstdint>
#include <vector>
#include "Number.h"

namespace code_learning {

	namespace algorithm {

		class BitSet {
		public:
			BitSet(uint64_t value);
			const std::string GetString();
		private:
			std::vector<char> m_bits;
		};

	}

}

#endif