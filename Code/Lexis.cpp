#include "Lexis.h"
namespace code_learning {
	namespace code {
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
				ContentAppend(next);
				return true;
			}
		}

		bool Lexis::ContentAppend(char next) {
			m_content.push_back(next);
			m_last = JudgeCharType(next);
			return false;
		}

		bool Lexis::IsMulti() const {
			return CharHighOne(m_content.front());
		}

		bool Lexis::IsSpace()const {
			return CHAR_TYPE_SPACE == JudgeCharType(m_content.front());
		}

		bool Lexis::IsNewLine()const {
			return '\n' == m_content.front() || '\r' == m_content.front();
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
		
	}
}