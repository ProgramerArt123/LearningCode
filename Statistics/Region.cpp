#include <iostream>
#include "Code/Region.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Glob &glob) :
			Composite<statistics::Line>(content, glob) {
		}
		void Region::Statistics(code::Region &region) {
			m_signature = region.GetSignature();
			for (auto &line : region.m_children.front()) {
				auto &result = m_children.Get(line->GetSignature(), line->GetContent());
				result.m_element.Statistics(*(code::Line*)(line.get()));
				result++; 
			}
			m_children.Sort();

			for (auto &line : m_children) {
				for (auto &symmetry : line->m_element.m_symmetries) {
					m_symmetries[symmetry.first] += symmetry.second;
				}
			}
		}
		void Region::Summary()const {
			std::cout << "============================================================" << std::endl;
			std::cout << "Region:" << m_signature << std::endl;
			for (auto &line : m_children) {
				line->Summary();
			}
			std::cout << "============================================================" << std::endl;
		}
	}
}