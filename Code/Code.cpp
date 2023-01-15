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
		Code::Code(const char *content):m_content(content){
			"代码学习";
			
		}

		void Code::Statistics(ListMap<Frequency<statistics::Region, statistics::Region>> &regions)const {
			for (auto &region : m_regions) {
				auto &result = regions.Get(region->GetSignature(), region->GetContent());
				const std::shared_ptr<statistics::Region> &element = 
					std::dynamic_pointer_cast<statistics::Region>(result.m_element);
				element->Statistics(*region);
				result++;
			}
			regions.Sort();
		}

		void Code::Decomposition(const Glob &glob) {
			for (const auto &c : m_content) {
				if (m_regions.empty()) {
					m_regions.push_back(std::unique_ptr<Region>(new Region()));
				}
				auto &lastRegion = m_regions.back();
				if (lastRegion->ContentAppend(c, glob)) {
					m_regions.push_back(std::unique_ptr<Region>(new Region()));
				}
			}

			for (auto &region : m_regions) {
				region->Decomposition(glob);
			}
		}

	}
}