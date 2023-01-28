#ifndef __CODE_LEARNING_CODE_LEXIS_TYPE_H__
#define __CODE_LEARNING_CODE_LEXIS_TYPE_H__

#include <string>

namespace code_learning {
	namespace code {
		enum LEXIS_TYPE {
			LEXIS_TYPE_NONE,
			LEXIS_TYPE_SPACE,
			LEXIS_TYPE_SYMBOL,
			LEXIS_TYPE_DIGITAL,
			LEXIS_TYPE_ALPHABET,
			LEXIS_TYPE_NAME
		};

		struct LexisType {
			LEXIS_TYPE m_type = LEXIS_TYPE_NONE;
			const char *m_name = "LEXIS_TYPE_NONE";
		};

		LexisType lexisTypes[];

		LEXIS_TYPE JudgeLexisType(const std::string &content);
	}
}

#endif