#include <iostream>
#include "Code/Region.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Glob &glob) :
			Element(content, glob), m_lines(glob) {
		}
		void Region::Statistics(code::Region &region) {
			m_signature = region.GetSignature();
			for (auto &line : region.m_children) {
				auto &result = m_lines.Get(line->GetSignature(), line->GetContent());
				result.m_element.Statistics(*line);
				result++; 
			}
			m_lines.Sort();

			for (auto &line : m_lines) {
				for (auto &symmetry : line->m_element.m_symmetries) {
					m_symmetries[symmetry.first] += symmetry.second;
				}
			}
		}
		void Region::Summary()const {
			std::cout << "============================================================" << std::endl;
			std::cout << "Region:" << m_signature << std::endl;
			for (auto &line : m_lines) {
				line->Summary();
			}
			std::cout << "============================================================" << std::endl;
		}
	}
}