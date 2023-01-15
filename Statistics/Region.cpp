#include <iostream>
#include "Code/Region.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Glob &glob) :
			Composite<statistics::Element, statistics::Line, statistics::Block>(content, glob) {
		}
		void Region::Statistics(code::Region &region) {
			m_signature = region.GetSignature();
			StatisticsLines(region);
			StatisticsBlocks(region);
		}
		void Region::Summary()const {
			std::cout << "============================================================" << std::endl;
			std::cout << "Region:" << m_signature << std::endl;

			ListMap<Frequency<statistics::Line, statistics::Line>> *statisticsChild =
				(ListMap<Frequency<statistics::Line, statistics::Line>>*)(m_children.front().get());

			for (auto &line : *statisticsChild) {
				line->Summary();
			}
			std::cout << "============================================================" << std::endl;
		}

		void Region::StatisticsLines(code::Region &region) {
			ListMap<Frequency<statistics::Line, statistics::Line>> *statisticsChild =
				(ListMap<Frequency<statistics::Line, statistics::Line>>*)(m_children.front().get());

			for (auto &child : region.m_children.front()) {
				const std::shared_ptr<code::Line> &line = std::dynamic_pointer_cast<code::Line>(child);
				auto &result = statisticsChild->Get(line->GetSignature(), line->GetContent());
				const std::shared_ptr<statistics::Line> &element =
					std::dynamic_pointer_cast<statistics::Line>(result.m_element);
				element->Statistics(*line);
				result++;
			}
			statisticsChild->Sort();

			for (auto &line : *statisticsChild) {
				const std::shared_ptr<statistics::Line> &element =
					std::dynamic_pointer_cast<statistics::Line>(line->m_element);
				for (auto &symmetry : element->m_symmetries) {
					m_symmetries[symmetry.first] += symmetry.second;
				}
			}
		}

		void Region::StatisticsBlocks(code::Region &region) {
			ListMap<Frequency<statistics::Block, statistics::Block>> *statisticsChild =
				(ListMap<Frequency<statistics::Block, statistics::Block>>*)(m_children.back().get());

			for (auto &child : region.m_children.back()) {
				const std::shared_ptr<code::Block> &line = std::dynamic_pointer_cast<code::Block>(child);
				auto &result = statisticsChild->Get(line->GetSignature(), line->GetContent());
				const std::shared_ptr<statistics::Block> &element =
					std::dynamic_pointer_cast<statistics::Block>(result.m_element);
				element->Statistics(*line);
				result++;
			}
			statisticsChild->Sort();

			for (auto &line : *statisticsChild) {
				const std::shared_ptr<statistics::Block> &element =
					std::dynamic_pointer_cast<statistics::Block>(line->m_element);
				for (auto &symmetry : element->m_symmetries) {
					m_symmetries[symmetry.first] += symmetry.second;
				}
			}
		}
	}
}