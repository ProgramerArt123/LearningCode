#include "BitSet.h"

namespace code_learning {

	namespace algorithm {
		BitSet::BitSet(uint64_t value) {
			while(value) {
				m_bits.push_back('0' + (value & 0x01));
				value >>= 1;
			};
		}
		const std::string BitSet::GetString() {
			return std::string(m_bits.crbegin(), m_bits.crend());
		}
	}

}