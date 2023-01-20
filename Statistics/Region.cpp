#include <iostream>
#include "Code/Region.h"
#include "Region.h"

namespace code_learning {
	namespace statistics {
		Region::Region(const std::string &content, Glob &glob) :
			Composite(content, glob) {
		}
		void Region::Statistics(code::Element &element) {
			m_signature = element.GetSignature();
			SetChildrenCount(element.GetChildrenCount());
			for (size_t index = 0; index < m_children.size(); index ++) {
				for (auto &child : *element.GetChild(index)) {
					auto &result = m_children[index]->Get(*child,
						child->GetSignature(), child->GetContent());
					result.Statistics(*child);
					result++;
				}
				m_children[index]->m_children.Sort();
				for (auto &child : *m_children[index]) {
					for (auto &symmetry : child->GetSymmetries()) {
						m_symmetries[symmetry.first] += symmetry.second;
					}
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