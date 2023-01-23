#ifndef __CODE_LEARNING_CONFIG_H__
#define __CODE_LEARNING_CONFIG_H__

#include <set>
#include <boost/rational.hpp>

namespace code_learning {
	
	class Config {
	public:
		explicit Config();

		std::set<char> ignores;
		std::set<char> splits;

		const boost::rational<uint16_t> m_symmetry;
	};
}

#endif