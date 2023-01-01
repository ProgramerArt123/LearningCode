#include <cstring>
#include <iostream>
#include "Config.h"
#include "Lexis.h"
#include "Statistics/Word.h"
#include "Region.h"

namespace code_learning {
	namespace code {
		
		bool Region::ContentAppend(char c) {
			if (IsReLine(c)) {
				re_line_count++;
				if (!m_children.empty()) {
					if (re_line_count >= 2) {
						m_children.pop_back();
						SetContent();
						return true;
					}
					else {
						m_children.push_back(std::unique_ptr<Line>(new Line()));
					}
				}
			}
			else {
				re_line_count = 0;
				if (m_children.empty()) {
					m_children.push_back(std::unique_ptr<Line>(new Line()));
				}
				auto &lastLine = m_children.back();
				lastLine->ContentAppend(c);
			}
			return false;
		}
		std::string Region::GetPattern(const Config &cfg)const {
			std::string pattern;
			pattern.append("[");
			for (auto &line : m_children) {
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
			for (const auto &child : m_children) {
				if (!m_content.empty()) {
					m_content.append("\n");
				}
				m_content.append(child->GetContent());
			}
		}
	}
}