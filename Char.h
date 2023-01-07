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

	struct Symmetry{
		bool operator<(const Symmetry &other) const {
			if (m_left < other.m_left) {
				return true;
			}
			if (m_left > other.m_left) {
				return false;
			}
			if (m_right < other.m_right) {
				return true;
			}
			if (m_right > other.m_right) {
				return false;
			}
			return false;
		}
		char m_left = ' ';
		char m_right = ' ';
	};

	extern Symmetry symmetries[4];

	bool IsSymmetry(char c);

	bool IsReLine(char c);

	CHAR_TYPE JudgeCharType(char c);

	uint8_t CharHighOne(char c);
}

#endif