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
		Code::Code(const std::string &content, const std::string &fileName) :Source(fileName) {
			m_type = ELEMENT_TYPE_CODE;
			m_file_count = 1;
			"代码学习";
			SetContent(content);
		}
		
		void Code::SetContent(const std::string &content) {
			m_content = content;
		}
		void Code::Decomposition(const Glob &glob) {
			for (const auto &c : m_content) {
				ContentAppendRegion(c, glob);
				ContentAppendBlock(c, glob);
			}
			code::Composite<code::Region, code::Block>::Decomposition(glob);
		}

		
		uint64_t Code::Scan(const Glob &glob) {
			Decomposition(glob);
			return m_file_count;
		}
		void Code::CallBack(std::function<void(const code::Element &)> factor) const {
			factor(*this);
		}
		void Code::ContentAppendRegion(char next, const Glob &glob) {
			if (m_children.front().empty()) {
				m_children.front().push_back(std::shared_ptr<code::Region>(new code::Region()));
			}
			auto &lastRegion = m_children.front().back();
			if (lastRegion->ContentAppend(next, glob)) {
				m_children.front().push_back(std::shared_ptr<code::Region>(new code::Region()));
			}
		}
		void Code::ContentAppendBlock(char next, const Glob &glob) {
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
	}
}