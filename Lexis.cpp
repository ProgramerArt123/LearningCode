#include "Lexis.h"
namespace code_learning {

	Lexis::Lexis(char first) {
		m_content.push_back(first);
		m_last = code_learning_char::JudgeType(first);
	}

	bool Lexis::TryAppendChar(char last) {
		if (IsDisconnection(last)) {
			return false;
		}
		else {
			m_content.push_back(last);
			m_last = code_learning_char::JudgeType(last);
			return true;
		}
	}

	bool Lexis::IsDisconnection(char last) {
		CHAR_TYPE type = code_learning_char::JudgeType(last);
		switch (m_last)
		{
		case CHAR_TYPE_SPACE:
			return CHAR_TYPE_SPACE != type;
			break;
		case CHAR_TYPE_SYMBOL:
			return true;
			break;
		case CHAR_TYPE_DIGITAL:
			return CHAR_TYPE_DIGITAL != type && CHAR_TYPE_ALPHABET != type;
			break;
		case CHAR_TYPE_ALPHABET:
			return CHAR_TYPE_ALPHABET != type && CHAR_TYPE_ALPHABET != type;
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