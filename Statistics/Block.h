#ifndef __CODE_LEARNING_STATISTICS_BLOCK_H__
#define __CODE_LEARNING_STATISTICS_BLOCK_H__

#include "Config.h"
#include "Generate.h"
#include "Lexis.h"
#include "CountAdjacencies.hpp"
#include "Composite.hpp"
#include "Code/Lexis.h"
#include "Descriptions.h"
#include "FrequenciesFacade.h"

namespace code_learning {
	namespace code {
		class Block;
	}
	namespace statistics {
		class Block : public Composite<statistics::LexisFacade> {
		public:
			explicit Block(const std::string &content, Glob &glob);
			void Statistics(code::Element &element)override;
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


		typedef ConcreteFacade<statistics::Block> BlockFacade;
	}
}

#endif