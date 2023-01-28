#include <iostream>
#include "Code/Char.h"
#include "Code/Lexis.h"
#include "Lexis.h"

namespace code_learning {
	namespace statistics {
		Lexis::Lexis(const std::string &content, Glob &glob) :
			Element(content, glob) {
			m_type = code::JudgeLexisType(content);
		}

		code::LEXIS_TYPE Lexis::GetType()const {
			return m_type;
		}

		
		void Lexis::Statistics(const code::Element &element)  {
		}
	}
}