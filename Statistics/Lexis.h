#ifndef __CODE_LEARNING_STATISTICS_LEXIS_H__
#define __CODE_LEARNING_STATISTICS_LEXIS_H__

#include <string>
#include "Code/LexisType.h"
#include "Element.h"
#include "ListMap.hpp"
#include "Frequency.hpp"
#include "FrequenciesFacade.h"

namespace code_learning {

	class Config;
	namespace statistics {
		class Lexis : public Element {
		public:
			Lexis(const std::string &content, Glob &glob);
			code::LEXIS_TYPE GetType() const;
			void Statistics(const code::Element &element) override;
		protected:
			code::LEXIS_TYPE m_type = code::LEXIS_TYPE_NONE;
		};

	}

}

#endif