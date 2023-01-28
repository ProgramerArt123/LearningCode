#ifndef __CODE_LEARNING_STATISTICS_DESCRIPTIONS_H__
#define __CODE_LEARNING_STATISTICS_DESCRIPTIONS_H__

#include <list>
#include <memory>

#include "Description.h"

namespace code_learning {
	
	class Config;
	namespace statistics {
		class Descriptions {
		public:
			Descriptions();
			void AddDescription(const std::string &content);
			Description &GetDescription(const std::string &content);
			std::list<std::unique_ptr<Description>>::const_iterator begin() const {
				return m_descs.begin();
			}
			std::list<std::unique_ptr<Description>>::const_iterator end() const {
				return m_descs.end();
			}
		private:
			std::list<std::unique_ptr<Description>> m_descs;
		};
	}
}

#endif