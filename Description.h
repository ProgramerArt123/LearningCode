#ifndef __CODE_LEARNING_DESCRIPTION_H__
#define __CODE_LEARNING_DESCRIPTION_H__

#include "AdjacencyWords.h"

namespace code_learning {

	struct Config;

	class Description {
	public:
		explicit Description(const std::string &content, const Config &cfg);
	
		const std::string m_content;
		AdjacencyWords m_front;
		AdjacencyWords m_back;
	};
}

#endif