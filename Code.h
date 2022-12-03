#ifndef __CODE_LEARNING_CODE_H__
#define __CODE_LEARNING_CODE_H__

#include <list>
#include <memory>
#include "Lexis.h"
#include "Config.h"

namespace code_learning {
	class Code {
	public:
		explicit Code(const char *content, const Config &cfg);
		const std::list<std::unique_ptr<Lexis>> &GetLexes() const;
	private:
		std::list<std::unique_ptr<Lexis>> m_lexes;
	};
}

#endif