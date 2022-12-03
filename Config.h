#ifndef __CODE_LEARNING_CONFIG_H__
#define __CODE_LEARNING_CONFIG_H__

#include <set>

namespace code_learning {
	struct Config {
		std::set<char> ignores;
		std::set<char> splits;
	};
}

#endif