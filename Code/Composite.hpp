#ifndef __CODE_LEARNING_CODE_COMPOSITE_HPP__
#define __CODE_LEARNING_CODE_COMPOSITE_HPP__

#include <list>
#include <vector>
#include <memory>

#include "Glob.h"
#include "Element.h"
#include "LexisType.h"

namespace code_learning {
	class Glob;

	namespace code {

		template<typename ...Children> class Composite;

		template<typename Child>
		class Composite<Child> : public code::Element {
		public:
			Composite() {
				m_children.resize(m_children.size() + 1);
			}
			
			std::string GetPattern() const override{
				std::string pattern;
				pattern.append("[");
				for (const auto &child : m_children.front()) {
					code::LEXIS_TYPE type = JudgeLexisType(std::string(child->begin(), child->end()));
					if (code_learning::code::LEXIS_TYPE_SPACE != type) {
						pattern.append(child->GetSignature());
						pattern.append(",");
					}
				}
				pattern.append("]");
				return pattern;
			}

			void Decomposition(const Glob &glob) override {
				for (auto &child : m_children) {
					for (auto &element : child) {
						element->Decomposition(glob);
					}
				}
				Element::Decomposition(glob);
			}
			size_t GetChildrenCount()const override {
				return m_children.size();
			}
			const std::list<std::shared_ptr<Element>> *GetChild(size_t index)const override {
				return &m_children[index];
			}
						
		public:
			std::vector<std::list<std::shared_ptr<Element>>> m_children;
		};

		template<typename Child, typename ...Children>
		class Composite<Child, Children...> : public Composite<Children...>{
		public:
			Composite() {
				Composite<Children...>::m_children.resize(Composite<Children...>::m_children.size() + 1);
			}
		};
	}
}

#endif