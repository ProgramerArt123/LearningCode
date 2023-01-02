#ifndef __CODE_LEARNING_CONFIG_H__
#define __CODE_LEARNING_CONFIG_H__

#include <set>

namespace code_learning {
	
	class Config {
	public:
		std::set<char> ignores;
		std::set<char> splits;
		uint8_t symmetry_percent = 90;
	};
}

#endif