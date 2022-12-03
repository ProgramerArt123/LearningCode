#ifndef __CODE_LEARNING_SOURCE_FILE_H__
#define __CODE_LEARNING_SOURCE_FILE_H__

#include <memory>
#include "Code.h"
#include "Config.h"

namespace code_learning {
	class SourceFile {
	public:
		explicit SourceFile(const char *fileName);
		void Scan(const Config &cfg);
		std::list<std::unique_ptr<Lexis>>::const_iterator begin() const;
		std::list<std::unique_ptr<Lexis>>::const_iterator end() const;
	private:
		std::unique_ptr<Code> m_code;
		std::string m_content;
	};
}

#endif