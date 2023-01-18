#ifndef __CODE_LEARNING_STATISTICS_ELEMENT_H__
#define __CODE_LEARNING_STATISTICS_ELEMENT_H__

#include <string>
#include <map>

namespace code_learning {

	class Glob;

	namespace code {
		class Element;
	}

	namespace statistics {

		class Element {
		public:
			explicit Element(const std::string &content, Glob &glob);
			virtual void Sort();
			virtual void Summary()const;
			const std::string &GetContent()const {
				return m_content;
			}
			virtual void Statistics(code::Element &element) = 0;
		protected:
			const std::string m_content;
			Glob &m_glob;
		public:
			std::map<char, uint64_t> m_symmetries;
		};

	}

}

#endif