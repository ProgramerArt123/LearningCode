#include <iostream>
#include "Code/Region.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Glob &glob) :
			Composite<statistics::Line, statistics::Line>(content, glob) {
		}
		void Region::Statistics(code::Region &region) {
			m_signature = region.GetSignature();

			for (auto &child : region.m_children.front()) {
				const std::shared_ptr<code::Line> &line = std::dynamic_pointer_cast<code::Line>(child);
				auto &result = m_children.front()->Get(line->GetSignature(), line->GetContent());
				result.m_element.Statistics(*line);
				result++; 
			}
			m_children.front()->Sort();

			for (auto &line : *m_children.front()) {
				for (auto &symmetry : line->m_element.m_symmetries) {
					m_symmetries[symmetry.first] += symmetry.second;
				}
			}
		}
		void Region::Summary()const {
			std::cout << "============================================================" << std::endl;
			std::cout << "Region:" << m_signature << std::endl;
			for (auto &line : *m_children.front()) {
				line->Summary();
			}
			std::cout << "============================================================" << std::endl;
		}
	}
}