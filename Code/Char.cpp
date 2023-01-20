#include "Char.h"

namespace code_learning {
	namespace code {
		Symmetry symmetries[] = {
			{'(', ')'},
			{'{', '}'},
			{'[', ']'},
			{'<', '>'}
		};

		bool IsSymmetry(char c) {
			return '(' == c || ')' == c || '{' == c || '}' == c ||
				'[' == c || ']' == c || '<' == c || '>' == c;
		}

		bool IsReLine(char c) {
			return '\n' == c || '\r' == c;
		}

		CHAR_TYPE JudgeCharType(char c) {
			if (' ' == c || '\n' == c || '\r' == c || '\t' == c) {
				return CHAR_TYPE_SPACE;
			}
			else if (('!' <= c && c <= '/') ||
				(':' <= c && c <= '@') ||
				('[' <= c && c <= '`') ||
				('{' <= c && c <= '~')) {
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
		uint8_t CharHighOne(char c) {
			if (!(c & 0x80)) {
				return 0;
			}
			if (!(c & 0x40)) {
				return 1;
			}
			if (!(c & 0x20)) {
				return 2;
			}
			if (!(c & 0x10)) {
				return 3;
			}
			if (!(c & 0x08)) {
				return 4;
			}
			return 0;
		}
	}
}