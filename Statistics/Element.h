#ifndef __CODE_LEARNING_STATISTICS_ELEMENT_H__
#define __CODE_LEARNING_STATISTICS_ELEMENT_H__

#include <string>

namespace code_learning {

	class Glob;

	namespace statistics {

		class Element {
		public:
			explicit Element(const std::string &content, Glob &glob);
			virtual void Sort();
			virtual void Summary()const;
		protected:
			const std::string m_content;
			std::string m_signature;
			Glob &m_glob;
		};

	}

}

#endif