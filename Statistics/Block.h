#ifndef __CODE_LEARNING_STATISTICS_BLOCK_H__
#define __CODE_LEARNING_STATISTICS_BLOCK_H__

#include "Config.h"
#include "Generate.h"
#include "Lexis.h"
#include "Adjacencies.hpp"
#include "Composite.hpp"
#include "Code/Lexis.h"
#include "Descriptions.h"

namespace code_learning {
	namespace code {
		class Block;
	}
	namespace statistics {
		class Block : public Composite<statistics::Element, statistics::Element> {
		public:
			explicit Block(const std::string &content, Glob &glob);
			void Statistics(code::Block &block);
			void Summary()const override;
		private:
			bool PeekWrap(std::list<std::shared_ptr<code::Element>>::const_iterator &lexis,
				std::list<std::shared_ptr<code::Element>>::const_iterator end);
			bool PeekWrap(std::list<std::shared_ptr<code::Element>>::const_iterator &lexis,
				std::list<std::shared_ptr<code::Element>>::const_iterator end) const;

		private:
			Descriptions m_descs;
			Wrapper m_wrapper;
		};
	}
}

#endif