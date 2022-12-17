#include "Lexis.h"
namespace code_learning {

	Lexis::Lexis() {

	}

	Lexis::Lexis(char first) {
		m_content.push_back(first);
		m_last = JudgeCharType(first);
	}

	bool Lexis::TryAppendChar(char next) {
		if (IsDisconnection(next)) {
			return false;
		}
		else {
			AppendChar(next);
			return true;
		}
	}

	void Lexis::AppendChar(char next) {
		m_content.push_back(next);
		m_last = JudgeCharType(next);
	}

	bool Lexis::IsDescription() const {
		return m_is_desc || CharHighOne(m_content.front());
	}

	bool Lexis::IsSpace()const {
		return CHAR_TYPE_SPACE == JudgeCharType(m_content.front());
	}

	void Lexis::SetDesc() {
		m_is_desc = true;
	}

	bool Lexis::IsDisconnection(char next) {
		CHAR_TYPE type = JudgeCharType(next);
		switch (m_last)
		{
		case CHAR_TYPE_SPACE:
			return CHAR_TYPE_SPACE != type;
			break;
		case CHAR_TYPE_SYMBOL:
			if ('_' != m_content.back()) {
				return true;
			}
			else {
				return CHAR_TYPE_DIGITAL != type && CHAR_TYPE_ALPHABET != type;
			}
			break;
		case CHAR_TYPE_DIGITAL:
			return CHAR_TYPE_DIGITAL != type && CHAR_TYPE_ALPHABET != type && '_' != next;
			break;
		case CHAR_TYPE_ALPHABET:
			return CHAR_TYPE_ALPHABET != type && CHAR_TYPE_ALPHABET != type && '_' != next;
			break;
		default:
			return false;
			break;
		}
	}
	std::list<char>::const_iterator Lexis::begin() const {
		return m_content.begin();
	}
	std::list<char>::const_iterator Lexis::end() const {
		return m_content.end();
	}
}