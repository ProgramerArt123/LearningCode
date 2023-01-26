#include "Lexis.h"
namespace code_learning {
	namespace code {
		Lexis::Lexis() {
			m_type = ELEMENT_TYPE_LEXIS;
		}

		Lexis::Lexis(char first) {
			m_content.push_back(first);
			m_last = JudgeCharType(first);
		}

		bool Lexis::TryAppendChar(char next, const Glob &glob) {
			if (IsDisconnection(next)) {
				return false;
			}
			else {
				ContentAppend(next, glob);
				return true;
			}
		}

		bool Lexis::ContentAppend(char next, const Glob &glob) {
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

		LEXIS_TYPE Lexis::JudgeLexisType(const std::string &content) {
			char preChar = 0;
			CHAR_TYPE preType = CHAR_TYPE_NONE;
			for (const auto &c : content) {
				CHAR_TYPE type = JudgeCharType(c);
				switch (type)
				{
				case CHAR_TYPE_SPACE:
					return LEXIS_TYPE_SPACE;
					break;
				case CHAR_TYPE_SYMBOL:
					return LEXIS_TYPE_SYMBOL;
					break;
				case CHAR_TYPE_DIGITAL:
					switch (preType)
					{
					case CHAR_TYPE_NONE:
					case CHAR_TYPE_DIGITAL:
						break;
					case CHAR_TYPE_ALPHABET:
						return LEXIS_TYPE_NAME;
						break;
					default:
						if ('_' == preChar) {
							return LEXIS_TYPE_NAME;
						}
						break;
					}
					break;
				case CHAR_TYPE_ALPHABET:
					switch (preType)
					{
					case CHAR_TYPE_NONE:
					case CHAR_TYPE_ALPHABET:
						break;
					case CHAR_TYPE_DIGITAL:
						return LEXIS_TYPE_NAME;
						break;
					default:
						if ('_' == preChar) {
							return LEXIS_TYPE_NAME;
						}
						break;
					}
					break;
				default:
					return LEXIS_TYPE_NONE;
					break;
				}
				preChar = c;
				preType = type;
			}
			switch (preType)
			{
			case code_learning::code::CHAR_TYPE_SPACE:
				return LEXIS_TYPE_SPACE;
				break;
			case code_learning::code::CHAR_TYPE_SYMBOL:
				return LEXIS_TYPE_SYMBOL;
				break;
			case code_learning::code::CHAR_TYPE_DIGITAL:
				return LEXIS_TYPE_DIGITAL;
				break;
			case code_learning::code::CHAR_TYPE_ALPHABET:
				return LEXIS_TYPE_ALPHABET;
				break;
			default:
				return LEXIS_TYPE_NONE;
				break;
			}
		}

	}
}