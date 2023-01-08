#ifndef __CODE_LEARNING_CODE_ELEMENT_H__
#define __CODE_LEARNING_CODE_ELEMENT_H__

#include <list>
#include <memory>
namespace code_learning {

	class Config;

	namespace code {

		class Element{
		public:
			virtual bool ContentAppend(char c) = 0;
			const std::string &GetContent() const;
			std::string::const_iterator begin() const;
			std::string::const_iterator end() const;
		protected:
			std::string m_content;
		};

	}
}

#endif