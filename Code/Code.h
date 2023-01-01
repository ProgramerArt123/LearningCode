#ifndef __CODE_LEARNING_CODE_CODE_H__
#define __CODE_LEARNING_CODE_CODE_H__

#include <list>
#include <memory>
#include "Region.h"
#include "Statistics/Region.h"
#include "Frequency.hpp"

namespace code_learning {

	class Lexis;
	class Config;

	namespace code {

		class Code {
		public:
			explicit Code(const char *content);
			void Statistics(ListMap<Frequency<statistics::Region>> &regions)const;
			void Decomposition(const Config &cfg);
		private:
			std::list<std::unique_ptr<code::Region>> m_regions;
		};
	}
}

#endif