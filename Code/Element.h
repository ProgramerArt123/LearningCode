#ifndef __CODE_LEARNING_CODE_ELEMENT_H__
#define __CODE_LEARNING_CODE_ELEMENT_H__

#include <list>
#include <vector>
#include <memory>
namespace code_learning {

	class Glob;

	namespace code {

		enum ELEMENT_TYPE {
			ELEMENT_TYPE_NONE,
			ELEMENT_TYPE_LEXIS,
			ELEMENT_TYPE_BLOCK,
			ELEMENT_TYPE_LINE,
			ELEMENT_TYPE_REGION,
			ELEMENT_TYPE_CODE,
			ELEMENT_TYPE_FILE,
			ELEMENT_TYPE_PATH
		};

		class Element{
		public:
			ELEMENT_TYPE GetType() const;
			virtual bool ContentAppend(char next, const Glob &glob);
			virtual bool TryAppendChar(char next, const Glob &glob);
			virtual bool IsSpace()const;
			virtual bool IsMulti()const ;
			virtual std::string GetPattern() const = 0;
			virtual void Decomposition(const Glob &glob);
			void CalculateSignature();
			virtual rsize_t GetChildrenCount()const;
			virtual const std::list<std::shared_ptr<Element>> *GetChild(size_t index)const;
			const std::string &GetContent() const;
			const std::string &GetSignature() const;
			std::string::const_iterator begin() const;
			std::string::const_iterator end() const;
		protected:
			std::string m_content;
			std::string m_signature;
			ELEMENT_TYPE m_type = ELEMENT_TYPE_NONE;
		};

	}
}

#endif