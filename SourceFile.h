#ifndef __CODE_LEARNING_SOURCE_FILE_H__
#define __CODE_LEARNING_SOURCE_FILE_H__

#include <memory>
#include "Code.h"
#include "Lexis.h"

namespace code_learning {

	
	class Config;

	class SourceFile {
	public:
		explicit SourceFile(const char *fileName);
		void Scan(const Config &cfg);
		std::list<std::unique_ptr<Lexis>>::const_iterator begin() const;
		std::list<std::unique_ptr<Lexis>>::const_iterator end() const;
		std::string PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis, const Config &cfg)const;
		bool PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis, const std::string &wrap)const;
	private:
		std::unique_ptr<Code> m_code;
		std::string m_content;
	};
}

#endif