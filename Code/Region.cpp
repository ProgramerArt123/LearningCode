#include <cstring>
#include <iostream>
#include "Config.h"
#include "Lexis.h"
#include "Block.h"
#include "Region.h"

namespace code_learning {
	namespace code {
		Region::Region(){
			m_type = ELEMENT_TYPE_REGION;
		}
		bool Region::ContentAppend(char c, const Glob &glob) {
			return ContentAppendLine(c, glob);
		}
		
		void Region::SetContent() {
			for (const auto &child : m_children.front()) {
				if (!m_content.empty()) {
					m_content.append("\n");
				}
				m_content.append(child->GetContent());
			}
		}
		
		bool Region::ContentAppendLine(char next, const Glob &glob) {
			if (IsReLine(next)) {
				re_line_count++;
				if (!m_children.front().empty()) {
					if (re_line_count >= 2) {
						m_children.front().pop_back();
						SetContent();
						return true;
					}
					else {
						m_children.front().push_back(std::shared_ptr<Line>(new Line()));
					}
				}
			}
			else {
				re_line_count = 0;
				if (m_children.front().empty()) {
					m_children.front().push_back(std::shared_ptr<Line>(new Line()));
				}
				auto &lastLine = m_children.front().back();
				lastLine->ContentAppend(next, glob);
			}
			return false;
		}
	}
}