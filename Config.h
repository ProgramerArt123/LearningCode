#ifndef __CODE_LEARNING_CONFIG_H__
#define __CODE_LEARNING_CONFIG_H__

#include <set>
#include "Algorithm/Probability.h"

namespace code_learning {
	
	class Config {
	public:
		Config();

		std::set<char> ignores;
		std::set<char> splits;

		const algorithm::Probability m_symmetry;
	};
}

#endif