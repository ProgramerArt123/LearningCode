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
			explicit Code(const char *content, Config &cfg);
			void Statistics(ListMap<Frequency<statistics::Region>> &regions)const;
		private:
			std::list<std::unique_ptr<code::Region>> m_regions;
			Config &m_cfg;
		};
	}
}

#endif