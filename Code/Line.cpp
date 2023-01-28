#include <cstring>
#include <iostream>
#include "Glob.h"
#include "Lexis.h"
#include "LexisType.h"
#include "Line.h"

namespace code_learning {
	namespace code {
		Line::Line() {
			m_type = ELEMENT_TYPE_LINE;
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
					const std::shared_ptr<code::Element> &last = m_children.front().back();
					if (!last->TryAppendChar(c, glob)) {
						m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis(c)));
					}
				}
				else {
					m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis(c)));
				}
				isPreSplit = glob.m_cfg.splits.end() != glob.m_cfg.splits.find(c);
			}
			Composite<Lexis>::Decomposition(glob);
		}
		bool Line::ContentAppend(char next, const Glob &glob) {
			m_content += next;
			return false;
		}
		
		bool Line::CheckEncoding(const char *content, size_t &index, const Glob &glob) {
			uint8_t highOne = CharHighOne(content[index]);
			bool isMulti = highOne;
			if (highOne) {//描述性对象
				m_children.front().push_back(std::unique_ptr<Lexis>(new Lexis()));
				const std::shared_ptr<code::Element> &last = m_children.front().back();
				for (uint8_t one = 0; one < highOne; one++) {
					last->ContentAppend(content[index++], glob);
				}
			}
			return isMulti;
		}
	}
}