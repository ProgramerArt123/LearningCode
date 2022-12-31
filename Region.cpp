#include <iostream>
#include "Code.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Config &cfg) :
			Element(content, cfg), m_lines(cfg) {
		}
		void Region::Statistics(code::Region &region) {
			m_signature = region.GetSignature();
			int index = 0;
			for (auto &line : region.m_lines) {
				auto &result = m_lines[line->GetSignature()];
				result.m_element.Statistics(*line);
				result++;
				index++;
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