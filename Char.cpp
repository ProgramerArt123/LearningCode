#include "Char.h"

namespace code_learning_char {
	CHAR_TYPE JudgeType(char c) {
		if (' ' == c || '\n' == c || '\r' == c || '\t' == c) {
			return CHAR_TYPE_SPACE;
		}
		else if (('!' <= c && c <= '/') ||
			(':' <= c && c <= '@') || 
			('[' <= c && c <= '`') || 
			('{' <= c && c <= '~') ) {
			return CHAR_TYPE_SYMBOL;
		}
		else if ('0' <= c && c <= '9') {
			return CHAR_TYPE_DIGITAL;
		}
		else if (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z')) {
			return CHAR_TYPE_ALPHABET;
		}
		else {
			return CHAR_TYPE_NONE;
		}
	}
}