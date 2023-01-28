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
			explicit Code(const std::string &content, const std::string &fileName = "");
			void SetContent(const std::string &content);
			void Decomposition(const Glob &glob) override;
			virtual uint64_t Scan(const Glob &glob) override;
			virtual void CallBack(std::function<void(const code::Element &)> factor) const override;
			void ContentAppendRegion(char next, const Glob &glob);
			void ContentAppendBlock(char next, const Glob &glob);
		};
	}
}

#endif