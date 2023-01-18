#ifndef __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__
#define __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__

#include <vector>
#include "Element.h"
#include "ListMap.hpp"
#include "Frequency.hpp"

namespace code_learning {
	namespace statistics {

		class FrequenciesFacade;

		template<typename ...ConcreteFacades> class Composite;

		template<typename ConcreteFacade>
		class Composite<ConcreteFacade> : public statistics::Element {
		public:
			explicit Composite(const std::string &content, Glob &glob):
				Element(content, glob){
				std::shared_ptr<FrequenciesFacade> child(new ConcreteFacade(glob));
				m_children.push_back(child);
			}
		protected:
			std::string m_signature;
			std::vector<std::shared_ptr<FrequenciesFacade>> m_children;
		
		};

		template<typename ConcreteFacade, typename ...ConcreteFacades>
		class Composite<ConcreteFacade, ConcreteFacades...> : public Composite<ConcreteFacades...> {
		public:
			Composite(const std::string &content, Glob &glob):
				Composite<ConcreteFacades...>(content, glob){
				std::shared_ptr<FrequenciesFacade> child(new ConcreteFacade(glob));
				Composite<ConcreteFacades...>::m_children.push_back(child);
			}
		};
	}
}

#endif