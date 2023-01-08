#include <cstring>
#include <iostream>
#include "Config.h"
#include "Lexis.h"
#include "Statistics/Word.h"
#include "Region.h"

namespace code_learning {
	namespace code {
		
		bool Region::ContentAppend(char c) {
			ContentAppendBlock(c);
			return ContentAppendLine(c);
		}
		std::string Region::GetPattern(const Config &cfg)const {
			std::string pattern;
			pattern.append("[");
			for (auto &line : m_children.front()) {
				if (1 < pattern.length()) {
					pattern.append(",");
				}
				line->Decomposition(cfg);
				pattern.append(line->GetSignature());
			}
			pattern.append("]");
			return pattern;
		}
		void Region::SetContent() {
			for (const auto &child : m_children.front()) {
				if (!m_content.empty()) {
					m_content.append("\n");
				}
				m_content.append(child->GetContent());
			}
		}
		void Region::ContentAppendBlock(char c) {

		}
		bool Region::ContentAppendLine(char c) {
			if (IsReLine(c)) {
				re_line_count++;
				if (!m_children.front().empty()) {
					if (re_line_count >= 2) {
						m_children.front().pop_back();
						SetContent();
						return true;
					}
					else {
						m_children.front().push_back(std::unique_ptr<Line>(new Line()));
					}
				}
			}
			else {
				re_line_count = 0;
				if (m_children.front().empty()) {
					m_children.front().push_back(std::shared_ptr<Line>(new Line()));
				}
				auto &lastLine = m_children.front().back();
				lastLine->ContentAppend(c);
			}
			return false;
		}
	}
}