#ifndef __CODE_LEARNING_CODE_ELEMENT_H__
#define __CODE_LEARNING_CODE_ELEMENT_H__

#include <list>
#include <memory>
namespace code_learning {

	class Glob;

	namespace code {

		enum ELEMENT_TYPE {
			ELEMENT_TYPE_NONE,
			ELEMENT_TYPE_LEXIS,
			ELEMENT_TYPE_BLOCK,
			ELEMENT_TYPE_LINE,
			ELEMENT_TYPE_REGION
		};

		class Element{
		public:
			virtual ELEMENT_TYPE GetType() const = 0;
			virtual bool TryAppendChar(char next, const Glob &glob);
			virtual bool ContentAppend(char next, const Glob &glob) = 0;
			const std::string &GetContent() const;
			const std::string &GetSignature() const;
			std::string::const_iterator begin() const;
			std::string::const_iterator end() const;
		protected:
			std::string m_content;
			std::string m_signature;
		};

	}
}

#endif