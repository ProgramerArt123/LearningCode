#include <iostream>
#include "Code/Region.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Glob &glob) :
			Composite<statistics::LineFacade, statistics::BlockFacade>(content, glob) {
		}
		void Region::Statistics(code::Element &element) {
			code::Region &region = static_cast<code::Region&>(element);
			m_signature = region.GetSignature();
			StatisticsLines(region);
			StatisticsBlocks(region);
		}
		void Region::Summary()const {
			std::cout << "============================================================" << std::endl;
			std::cout << "Region:" << m_signature << std::endl;
			for (auto &line : *m_children.front()) {
				line->Summary();
			}
			std::cout << "============================================================" << std::endl;
		}

		void Region::StatisticsLines(code::Region &region) {
			for (auto &child : region.m_children.front()) {
				const std::shared_ptr<code::Line> &line = std::dynamic_pointer_cast<code::Line>(child);
				auto &result = m_children.front()->m_children.Get<Frequency<statistics::Line>>(
					line->GetSignature(), line->GetContent());
				result.m_element->Statistics(*line);
				result++;
			}
			m_children.front()->m_children.Sort();

			for (auto &line : *m_children.front()) {
				for (auto &symmetry : line->GetSymmetries()) {
					m_symmetries[symmetry.first] += symmetry.second;
				}
			}
		}

		void Region::StatisticsBlocks(code::Region &region) {
			
			for (auto &child : region.m_children.back()) {
				const std::shared_ptr<code::Block> &line = std::dynamic_pointer_cast<code::Block>(child);
				auto &result = m_children.front()->m_children.Get<Frequency<statistics::Block>>(
					line->GetSignature(), line->GetContent());
				result.m_element->Statistics(*line);
				result++;
			}
			m_children.back()->m_children.Sort();

			for (auto &block : *m_children.back()) {
				for (auto &symmetry : block->GetSymmetries()) {
					m_symmetries[symmetry.first] += symmetry.second;
				}
			}
		}
	}
}