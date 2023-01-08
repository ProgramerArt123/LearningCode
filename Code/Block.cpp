#include <cstring>
#include <iostream>
#include "Config.h"
#include "Lexis.h"
#include "Statistics/Word.h"
#include "Block.h"

namespace code_learning {
	namespace code {
		void Block::Decomposition(const Config &cfg) {
			size_t length = m_content.length();
			bool isPreSplit = false;
			for (size_t index = 0; index < length; index++) {
				isPreSplit = CheckEncoding(m_content.c_str(), index);
				if (index == length) {
					break;
				}
				char c = m_content[index];
				if (!isPreSplit && !m_children.front().empty()) {
					std::shared_ptr<Element> &last = m_children.front().back();
					//if (!last->TryAppendChar(c)) {
					//	m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis(c)));
					//}
				}
				else {
					m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis(c)));
				}
				isPreSplit = cfg.splits.end() != cfg.splits.find(c);
			}
			Composite<Element, Element>::Decomposition(cfg);
		}
		bool Block::ContentAppend(char c) {
			m_content += c;
			return false;
		}
		std::string Block::GetPattern(const Config &cfg) const {
			std::string pattern;
			pattern.append("[");
			for (const auto &lexis : m_children.front()) {
				WORD_TYPE type = statistics::Word::JudgeWordType(std::string(lexis->begin(), lexis->end()));
				if (code_learning::WORD_TYPE_SPACE != type) {
					if (1 < pattern.length()) {
						pattern.append(",");
					}
					pattern.append(wordTypes[type].m_name);
				}
			}
			pattern.append("]");
			return pattern;
		}
		bool Block::CheckEncoding(const char *content, size_t &index) {
			uint8_t highOne = CharHighOne(content[index]);
			bool isMulti = highOne;
			if (highOne) {//描述性对象
				m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis()));
				std::shared_ptr<Element> &last = m_children.front().back();
				for (uint8_t one = 0; one < highOne; one++) {
					last->ContentAppend(content[index++]);
				}
			}
			return isMulti;
		}
	}
}