#ifndef __CODE_LEARNING_STATISTICS_FREQUENCIES_FACADE_H__
#define __CODE_LEARNING_STATISTICS_FREQUENCIES_FACADE_H__

#include <memory>
#include <list>
#include "ListMap.hpp"

namespace code_learning {
	class Glob;
	namespace code {
		class Element;
	}
	namespace statistics {
		class FrequenciesFacade {
		public:
			explicit FrequenciesFacade(Glob &glob);
			std::list<std::shared_ptr<AdjacencyBase>>::const_iterator begin() const;
			std::list<std::shared_ptr<AdjacencyBase>>::const_iterator end() const;
			AdjacencyBase &Get(const code::Element &element, const std::string &key, const std::string &content);
			void Count(const code::Element &element, const std::string &key);
			void FrontCount(const code::Element &element, const std::string &key, const std::string &next);
			void BackCount(const code::Element &element, const std::string &key, const std::string &pre);
			ListMap m_children;
		};

	}
}

#endif