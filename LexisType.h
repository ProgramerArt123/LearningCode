#ifndef __CODE_LEARNING_LEXIS_TYPE_H__
#define __CODE_LEARNING_LEXIS_TYPE_H__

namespace code_learning {

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

}

#endif