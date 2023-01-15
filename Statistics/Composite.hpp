#ifndef __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__
#define __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__

#include <vector>
#include "Element.h"
#include "ListMap.hpp"
#include "Frequency.hpp"

namespace code_learning {
	namespace statistics {

		template<typename ...Children> class Composite;

		template<typename Base, typename Child>
		class Composite<Base, Child> : public statistics::Element {
		public:
			explicit Composite(const std::string &content, Glob &glob):
				Element(content, glob){
				std::shared_ptr<ListMapBase> child(new ListMap<Frequency<Base, Child>>(glob));
				m_children.push_back(child);
			}
		protected:
			std::string m_signature;
			std::vector<std::shared_ptr<ListMapBase>> m_children;
		public:
			std::map<char, uint64_t> m_symmetries;
		};

		template<typename Base, typename Child, typename ...Children>
		class Composite<Base, Child, Children...> : public Composite<Base, Children...> {
		public:
			Composite(const std::string &content, Glob &glob):
				Composite<Base, Children...>(content, glob){
				std::shared_ptr<ListMapBase> child(new ListMap<Frequency<Base, Child>>(glob));
				Composite<Base, Children...>::m_children.push_back(child);
			}
		};
	}
}

#endif