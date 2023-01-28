#include "Char.h"
#include "LexisType.h"

namespace code_learning {
	namespace code {
		LexisType lexisTypes[] = {
			{LEXIS_TYPE_NONE, "LEXIS_TYPE_NONE"},
			{LEXIS_TYPE_SPACE, "LEXIS_TYPE_SPACE"},
			{LEXIS_TYPE_SYMBOL, "LEXIS_TYPE_SYMBOL"},
			{LEXIS_TYPE_DIGITAL, "LEXIS_TYPE_DIGITAL"},
			{LEXIS_TYPE_ALPHABET, "LEXIS_TYPE_ALPHABET"},
			{LEXIS_TYPE_NAME, "LEXIS_TYPE_NAME"}
		};

		LEXIS_TYPE JudgeLexisType(const std::string &content) {
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
