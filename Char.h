#ifndef __CODE_LEARNING_CHAR_H__
#define __CODE_LEARNING_CHAR_H__



namespace code_learning{

	enum CHAR_TYPE {
		CHAR_TYPE_NONE,
		CHAR_TYPE_SPACE,
		CHAR_TYPE_SYMBOL,
		CHAR_TYPE_DIGITAL,
		CHAR_TYPE_ALPHABET
	};

	CHAR_TYPE JudgeCharType(char c);
}

#endif