#ifndef __CODE_LEARNING_DESCRIPTION_H__
#define __CODE_LEARNING_DESCRIPTION_H__

#include "Adjacencies.hpp"

namespace code_learning {

	class Config;

	class Description {
	public:
		explicit Description(const std::string &content, const Config &cfg);
	
		const std::string m_content;
		std::string m_front;
		std::string m_back;
	};
}

#endif