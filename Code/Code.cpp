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
		Code::Code(const char *content, Config &cfg) :m_cfg(cfg) {
			"代码学习";
			size_t length = strlen(content);
			for (size_t index = 0; index < length; index++) {
				if (m_regions.empty()) {
					m_regions.push_back(std::unique_ptr<Region>(new Region(m_cfg)));
				}
				char c = content[index];
				auto &lastRegion = m_regions.back();
				if (lastRegion->ContentAppend(c)) {
					m_regions.push_back(std::unique_ptr<Region>(new Region(m_cfg)));
				}
			}
			for (auto &region : m_regions) {
				region->Decomposition(cfg);
			}
		}

		void Code::Statistics(ListMap<Frequency<statistics::Region>> &regions)const {
			for (auto &region : m_regions) {
				auto &result = regions.Get(region->GetSignature(), region->GetContent());
				result.m_element.Statistics(*region);
				result++;
			}
			regions.Sort();
		}

		

	}
}