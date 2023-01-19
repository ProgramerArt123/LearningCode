#ifndef __CODE_LEARNING_STATISTICS_LEXIS_H__
#define __CODE_LEARNING_STATISTICS_LEXIS_H__

#include <string>
#include "LexisType.h"
#include "Element.h"
#include "ListMap.hpp"
#include "Frequency.hpp"
#include "FrequenciesFacade.h"

namespace code_learning {

	class Config;
	namespace statistics {
		class Lexis : public Element {
		public:
			explicit Lexis(const std::string &content, Glob &glob);
			LEXIS_TYPE GetType() const;
			static LEXIS_TYPE JudgeLexisType(const std::string &content);
			void Statistics(code::Element &element) override{
			}
		protected:
			LEXIS_TYPE m_type = LEXIS_TYPE_NONE;
		};


		typedef ConcreteFacade<statistics::Lexis> LexisFacade;
	}

}

#endif