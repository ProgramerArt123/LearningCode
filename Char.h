#ifndef __CODE_LEARNING_CHAR_H__
#define __CODE_LEARNING_CHAR_H__

#include <cstdint>

namespace code_learning{

	enum CHAR_TYPE {
		CHAR_TYPE_NONE,
		CHAR_TYPE_SPACE,
		CHAR_TYPE_SYMBOL,
		CHAR_TYPE_DIGITAL,
		CHAR_TYPE_ALPHABET
	};

	bool IsReLine(char c);

	CHAR_TYPE JudgeCharType(char c);

	uint8_t CharHighOne(char c);
}

#endif