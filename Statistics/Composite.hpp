#ifndef __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__
#define __CODE_LEARNING_STATISTICS_COMPOSITE_HPP__

#include "Element.h"
#include "ListMap.hpp"
#include "Frequency.hpp"

namespace code_learning {
	namespace statistics {
		template<typename Child>
		class Composite : public Element {
		public:
			explicit Composite(const std::string &content, Glob &glob):
				Element(content, glob), m_children(glob){}
		protected:
			std::string m_signature;
			ListMap<Frequency<Child>> m_children;
		public:
			std::map<char, uint64_t> m_symmetries;
		};
	}
}

#endif