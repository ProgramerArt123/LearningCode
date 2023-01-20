#ifndef __CODE_LEARNING_CODE_CODE_H__
#define __CODE_LEARNING_CODE_CODE_H__

#include <list>
#include <memory>
#include "Region.h"

namespace code_learning {
	class Config;

	namespace code {

		class Lexis;
		class Code {
		public:
			explicit Code(const char *content);
			void Decomposition(const Glob &glob);
			std::list<std::unique_ptr<code::Region>> m_regions;
		private:
			std::string m_content;
		};
	}
}

#endif