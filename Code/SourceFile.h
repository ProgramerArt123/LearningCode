#ifndef __CODE_LEARNING_CODE_SOURCE_FILE_H__
#define __CODE_LEARNING_CODE_SOURCE_FILE_H__

#include <memory>
#include "Config.h"
#include "Code.h"
#include "Lexis.h"
#include "SourcePath.h"

namespace code_learning {
	namespace code {
		class SourceFile : public Code {
		public:
			explicit SourceFile(const char *fileName);
			
			
		};
	}
}

#endif