#include <cstring>
#include <iostream>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include "Config.h"
#include "Lexis.h"
#include "Line.h"
#include "Region.h"
#include "Code.h"

namespace code_learning {
	namespace code {
		Code::Code(const char *content){
			m_content = content;
			m_file_count = 1;
			"代码学习";
		}

		void Code::Decomposition(const Glob &glob) {
			for (const auto &c : m_content) {
				if (m_children.front().empty()) {
					m_children.front().push_back(std::shared_ptr<Region>(new Region()));
				}
				auto &lastRegion = m_children.front().back();
				if (lastRegion->ContentAppend(c, glob)) {
					m_children.front().push_back(std::shared_ptr<Region>(new Region()));
				}
			}

			for (auto &region : m_children.front()) {
				region->Decomposition(glob);
			}
		}

		ELEMENT_TYPE Code::GetType() const {
			return ELEMENT_TYPE_CODE;
		}
		bool Code::ContentAppend(char next, const Glob &glob) {
			return false;
		}
		std::string Code::GetPattern(const Glob &glob)const {
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
		uint64_t Code::Scan(const Glob &glob) {
			Decomposition(glob);
			return m_file_count;
		}
		void Code::Foreach(std::function<void(const std::string &, const std::vector<std::list<std::shared_ptr<code::Element>>> &)> factor) const {
			factor("[code]", m_children);
		}
	}
}