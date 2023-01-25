#ifndef __CODE_LEARNING_CODE_SOURCE_FILE_H__
#define __CODE_LEARNING_CODE_SOURCE_FILE_H__

#include <memory>
#include "Config.h"
#include "Code.h"
#include "Lexis.h"
#include "SourcePath.h"

namespace code_learning {
	namespace code {
		class SourceFile : public SourcePath {

		public:
			explicit SourceFile(const char *fileName);
			uint64_t Scan(const Glob &glob) override;
			void Foreach(std::function<void(const std::string &, const std::vector<std::list<std::shared_ptr<code::Element>>> &)> factor) const override;

			std::unique_ptr<code::Code> m_code;
			std::string m_content;
			
		};
	}
}

#endif