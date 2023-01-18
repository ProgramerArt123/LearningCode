#ifndef __CODE_LEARNING_STATISTICS_FREQUENCIES_FACADE_H__
#define __CODE_LEARNING_STATISTICS_FREQUENCIES_FACADE_H__

#include <memory>

namespace code_learning {
	class Glob;
	namespace statistics {
		class FrequenciesFacade  {
		public:
			explicit FrequenciesFacade( Glob &glob):m_children(glob) {

			}
			std::list<std::shared_ptr<AdjacencyBase>>::const_iterator begin() const {
				return m_children.begin();
			}
			std::list<std::shared_ptr<AdjacencyBase>>::const_iterator end() const {
				return m_children.end();
			}
			virtual void Count(const std::string &key) = 0;
			virtual void FrontCount(const std::string &key, const std::string &next) = 0;
			virtual void BackCount(const std::string &key, const std::string &pre) = 0;

			ListMap m_children;
		};

	}
}

#endif