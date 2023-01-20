#ifndef __CODE_LEARNING_CODE_SOURCE_FILE_H__
#define __CODE_LEARNING_CODE_SOURCE_FILE_H__

#include <memory>
#include "Config.h"
#include "Code.h"
#include "Lexis.h"
#include "Source.h"

namespace code_learning {
	namespace code {
		class SourceFile : public Source {

		public:
			explicit SourceFile(const char *fileName);
			uint64_t Scan(const Glob &glob) override;
			void Foreach(std::function<void(const std::list<std::unique_ptr<code::Region>> &)> factor) const override;

			std::unique_ptr<code::Code> m_code;
			std::string m_content;
			std::string m_file_name;
		};
	}
}

#endif