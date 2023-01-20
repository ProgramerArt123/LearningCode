#ifndef __CODE_LEARNING_CODE_SOURCE_FILE_H__
#define __CODE_LEARNING_CODE_SOURCE_FILE_H__

#include <memory>
#include "Config.h"
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Statistics/Region.h"

namespace code_learning {
	namespace code {
		class SourceFile {

		public:
			explicit SourceFile(const char *fileName);
			void Scan(const Glob &glob);

			std::unique_ptr<code::Code> m_code;
			std::string m_content;
			std::string m_file_name;
		};
	}
}

#endif