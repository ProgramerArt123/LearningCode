#ifndef __CODE_LEARNING_CODE_CODE_H__
#define __CODE_LEARNING_CODE_CODE_H__

#include <list>
#include <memory>

#include "Block.h"

#include "Region.h"

#include "Composite.hpp"

namespace code_learning {
	class Config;

	namespace code {

		class Code : public code::Composite<code::Region, code::Block> {
		public:
			explicit Code(const char *content);
			void Decomposition(const Glob &glob) override;
			ELEMENT_TYPE GetType() const override {
				return ELEMENT_TYPE_FILE;
			}
			bool ContentAppend(char next, const Glob &glob) override {
				return false;
			}
			std::string GetPattern(const Glob &glob)const override {
				std::string pattern;
				pattern.append("[");
				for (auto &child : m_children.front()) {
					if (1 < pattern.length()) {
						pattern.append(",");
					}
					child->Decomposition(glob);
					pattern.append(child->GetSignature());
				}
				pattern.append("]");
				return pattern;
			}
		};
	}
}

#endif