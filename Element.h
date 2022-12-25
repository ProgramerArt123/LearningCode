#ifndef __CODE_LEARNING_ELEMENT_H__
#define __CODE_LEARNING_ELEMENT_H__

#include <string>

namespace code_learning {

	class Config;

	class Element {
	public:
		explicit Element(const std::string &content, const Config &cfg);
		virtual void Sort();
	};

}

#endif