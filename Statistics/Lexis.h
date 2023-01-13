#ifndef __CODE_LEARNING_STATISTICS_LEXIS_H__
#define __CODE_LEARNING_STATISTICS_LEXIS_H__

#include <string>
#include "LexisType.h"
#include "Element.h"

namespace code_learning {

	class Config;
	namespace statistics {
		class Lexis : public Element {
		public:
			explicit Lexis(const std::string &content, Glob &glob);
			const std::string &GetContent()const;
			LEXIS_TYPE GetType() const;
			static LEXIS_TYPE JudgeLexisType(const std::string &content);
		protected:
			const std::string m_content;
			LEXIS_TYPE m_type = LEXIS_TYPE_NONE;
		};
	}

}

#endif