#ifndef __CODE_LEARNING_CODE_CODE_H__
#define __CODE_LEARNING_CODE_CODE_H__

#include <list>
#include <memory>

#include "Block.h"

#include "Region.h"

#include "Composite.hpp"

#include "Source.h"

namespace code_learning {
	class Config;

	namespace code {

		class Code : public code::Composite<code::Region, code::Block>, public Source {
		public:
			explicit Code(const char *content);
			void Decomposition(const Glob &glob) override;
			ELEMENT_TYPE GetType() const override;
			bool ContentAppend(char next, const Glob &glob) override;
			std::string GetPattern(const Glob &glob)const override;
			virtual uint64_t Scan(const Glob &glob) override;
			virtual void Foreach(std::function<void(const std::string &, const std::vector<std::list<std::shared_ptr<code::Element>>> &)> factor) const override;
		};
	}
}

#endif