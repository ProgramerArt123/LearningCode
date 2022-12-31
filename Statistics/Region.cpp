#include <iostream>
#include "Code/Region.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Config &cfg) :
			Element(content, cfg), m_lines(cfg) {
		}
		void Region::Statistics(code::Region &region) {
			m_signature = region.GetSignature();
			for (auto &line : region.m_children) {
				auto &result = m_lines[line->GetSignature()];
				result.m_element.Statistics(*line);
				result++;
			}
			m_lines.Sort();
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