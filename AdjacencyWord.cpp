#include <iostream>
#include "Char.h"
#include "AdjacencyWord.h"

namespace code_learning {
	AdjacencyWord::AdjacencyWord(const std::string &content, const Config &cfg) :
		m_content(content) {
		m_type = JudgeWordType(content);
	}
	AdjacencyWord *AdjacencyWord::operator++(int) {
		m_count++;
		return this;
	}
	const std::string &AdjacencyWord::GetContent()const {
		return m_content;
	}
	uint64_t AdjacencyWord::GetCount()const {
		return m_count;
	}
	WORD_TYPE AdjacencyWord::GetType()const {
		return m_type;
	}
	WORD_TYPE AdjacencyWord::JudgeWordType(const std::string &content) {
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