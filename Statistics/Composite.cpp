#include "FrequenciesFacade.h"
#include "Composite.h"

namespace code_learning {
	namespace statistics {
		Composite::Composite(const std::string &content, Glob &glob) :
			Element(content, glob) {
		}
		void Composite::SetChildrenCount(size_t count) {
			if (count > m_children.size()) {
				for (size_t index = 0; index < count - m_children.size(); index++) {
					std::shared_ptr<FrequenciesFacade> child(new FrequenciesFacade(m_glob));
					m_children.push_back(child);
				}
			}
		}
		void Composite::Statistics(const code::Element &element) {
			m_signature = element.GetSignature();
			SetChildrenCount(element.GetChildrenCount());
			for (auto &child : m_children) {
				for (auto &element : *child) {
					for (auto &symmetry : element->GetSymmetries()) {
						m_symmetries[symmetry.first] += symmetry.second;
					}
				}
			}
		}
	}
}