#include <cstring>
#include <iostream>
#include "Config.h"
#include "Lexis.h"
#include "Statistics/Lexis.h"
#include "Region.h"

namespace code_learning {
	namespace code {
		ELEMENT_TYPE Region::GetType() const {
			return ELEMENT_TYPE_REGION;
		}
		bool Region::ContentAppend(char c, const Glob &glob) {
			ContentAppendBlock(c, glob);
			return ContentAppendLine(c, glob);
		}
		std::string Region::GetPattern(const Glob &glob)const {
			std::string pattern;
			pattern.append("[");
			for (auto &child : m_children.front()) {
				if (1 < pattern.length()) {
					pattern.append(",");
				}
				child->Decomposition(glob);
				pattern.append(child->GetSignature());
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
		void Region::ContentAppendBlock(char next, const Glob &glob) {
			if (m_children.back().empty()) {
				if (glob.m_generate.symmetries.find(next) !=
					glob.m_generate.symmetries.end()) {
					m_children.back().push_back(std::shared_ptr<Element>(new Block(next)));
				}
			}
			else {
				auto &lastBlock = m_children.back().back();
				if (!lastBlock->TryAppendChar(next, glob)) {
					if (glob.m_generate.symmetries.find(next) !=
						glob.m_generate.symmetries.end()) {
						m_children.back().push_back(std::shared_ptr<Element>(new Block(next)));
					}
				}
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