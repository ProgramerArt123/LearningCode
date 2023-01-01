#ifndef __CODE_LEARNING_WORD_TYPE_H__
#define __CODE_LEARNING_WORD_TYPE_H__

namespace code_learning {

	enum WORD_TYPE {
		WORD_TYPE_NONE,
		WORD_TYPE_SPACE,
		WORD_TYPE_SYMBOL,
		WORD_TYPE_DIGITAL,
		WORD_TYPE_ALPHABET,
		WORD_TYPE_NAME
	};

	struct WordType {
		WORD_TYPE m_type = WORD_TYPE_NONE;
		const char *m_name = "WORD_TYPE_NONE";
	};

	WordType wordTypes[];

}

#endif