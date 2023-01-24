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

	}
}