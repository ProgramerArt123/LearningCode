#ifndef __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__
#define __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__

#include <vector>
#include "Element.h"
#include "ListMap.hpp"
#include "Frequency.hpp"

namespace code_learning {
	namespace statistics {

		template<typename ...Children> class Composite;

		template<typename Child, typename Base>
		class Composite<Child, Base> : public statistics::Element {
		public:
			explicit Composite(const std::string &content, Glob &glob):
				Element(content, glob){
				for (int index = 0; index < m_children_count; index ++) {
					std::shared_ptr<ListMap<Frequency<Base>>> child(new ListMap<Frequency<Base>>(glob));
					m_children.push_back(child);
				}
			}
		protected:
			int m_children_count = 1;
			std::string m_signature;
			std::vector<std::shared_ptr<ListMap<Frequency<Base>>>> m_children;
		public:
			std::map<char, uint64_t> m_symmetries;
		};

		template<typename Child, typename ...Children>
		class Composite<Child, Children...> : public Composite<Children...> {
		public:
			Composite(const std::string &content, Glob &glob):
				Composite<Children...>(content, glob){
				Composite<Children...>::m_children_count ++;
			}
		};
	}
}

#endif