#include <iostream>
#include "Char.h"
#include "Word.h"

namespace code_learning {
	namespace statistics {
		Word::Word(const std::string &content, Glob &glob) :
			Element(content, glob), m_content(content) {
			m_type = JudgeWordType(content);
		}

		const std::string &Word::GetContent()const {
			return m_content;
		}

		WORD_TYPE Word::GetType()const {
			return m_type;
		}

		WORD_TYPE Word::JudgeWordType(const std::string &content) {
			char preChar = 0;
			CHAR_TYPE preType = CHAR_TYPE_NONE;
			for (const auto &c : content) {
				CHAR_TYPE type = JudgeCharType(c);
				switch (type)
				{
				case CHAR_TYPE_SPACE:
					return WORD_TYPE_SPACE;
					break;
				case CHAR_TYPE_SYMBOL:
					return WORD_TYPE_SYMBOL;
					break;
				case CHAR_TYPE_DIGITAL:
					switch (preType)
					{
					case CHAR_TYPE_NONE:
					case CHAR_TYPE_DIGITAL:
						break;
					case CHAR_TYPE_ALPHABET:
						return WORD_TYPE_NAME;
						break;
					default:
						if ('_' == preChar) {
							return WORD_TYPE_NAME;
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
						return WORD_TYPE_NAME;
						break;
					default:
						if ('_' == preChar) {
							return WORD_TYPE_NAME;
						}
						break;
					}
					break;
				default:
					return WORD_TYPE_NONE;
					break;
				}
				preChar = c;
				preType = type;
			}
			switch (preType)
			{
			case code_learning::CHAR_TYPE_SPACE:
				return WORD_TYPE_SPACE;
				break;
			case code_learning::CHAR_TYPE_SYMBOL:
				return WORD_TYPE_SYMBOL;
				break;
			case code_learning::CHAR_TYPE_DIGITAL:
				return WORD_TYPE_DIGITAL;
				break;
			case code_learning::CHAR_TYPE_ALPHABET:
				return WORD_TYPE_ALPHABET;
				break;
			default:
				return WORD_TYPE_NONE;
				break;
			}
		}
	}
}