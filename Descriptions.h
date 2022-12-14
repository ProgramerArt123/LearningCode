#ifndef __CODE_LEARNING_DESCRIPTIONS_H__
#define __CODE_LEARNING_DESCRIPTIONS_H__

#include <list>
#include <memory>

#include "Description.h"

namespace code_learning {
	
	struct Config;

	class Wrapper {
	public:
		std::string prefix;
		std::string suffix;
	};

	class Descriptions {
	public:
		explicit Descriptions(const Config &cfg);
		void AddDescription(const std::string &content);
		Description &GetDescription(const std::string &content);
		std::list<std::unique_ptr<Description>>::const_iterator begin() const {
			return m_descs.begin();
		}
		std::list<std::unique_ptr<Description>>::const_iterator end() const {
			return m_descs.end();
		}
	private:
		std::list<std::unique_ptr<Wrapper>> m_wrappers;
		std::list<std::unique_ptr<Description>> m_descs;
		const Config &m_cfg;
	};
}

#endif