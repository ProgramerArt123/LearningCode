#include <cstring>
#include <iostream>
#include "Glob.h"
#include "Lexis.h"
#include "Statistics/Lexis.h"
#include "Line.h"

namespace code_learning {
	namespace code {
		ELEMENT_TYPE Line::GetType() const {
			return ELEMENT_TYPE_LINE;
		}
		void Line::Decomposition(const Glob &glob) {
			size_t length = m_content.length();
			bool isPreSplit = false;
			for (size_t index = 0; index < length; index++) {
				isPreSplit = CheckEncoding(m_content.c_str(), index, glob);
				if (index == length) {
					break;
				}
				char c = m_content[index];
				if (!isPreSplit && !m_children.front().empty()) {
					std::shared_ptr<Lexis> &last = m_children.front().back();
					if (!last->TryAppendChar(c, glob)) {

						m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis(c)));
					}
				}
				else {
					m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis(c)));
				}
				isPreSplit = glob.m_cfg.splits.end() != glob.m_cfg.splits.find(c);
			}
			Composite<Lexis, Lexis>::Decomposition(glob);
		}
		bool Line::ContentAppend(char next, const Glob &glob) {
			m_content += next;
			return false;
		}
		std::string Line::GetPattern(const Glob &glob) const {
			std::string pattern;
			pattern.append("[");
			for (const auto &lexis : m_children.front()) {
				LEXIS_TYPE type = statistics::Lexis::JudgeLexisType(std::string(lexis->begin(), lexis->end()));
				if (code_learning::LEXIS_TYPE_SPACE != type) {
					if (1 < pattern.length()) {
						pattern.append(",");
					}
					pattern.append(lexisTypes[type].m_name);
				}
			}
			pattern.append("]");
			return pattern;
		}
		bool Line::CheckEncoding(const char *content, size_t &index, const Glob &glob) {
			uint8_t highOne = CharHighOne(content[index]);
			bool isMulti = highOne;
			if (highOne) {//描述性对象
				m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis()));
				std::shared_ptr<Lexis> &last = m_children.front().back();
				for (uint8_t one = 0; one < highOne; one++) {
					last->ContentAppend(content[index++], glob);
				}
			}
			return isMulti;
		}
	}
}