#ifndef __CODE_LEARNING_SOURCE_FILE_H__
#define __CODE_LEARNING_SOURCE_FILE_H__

#include <memory>
#include "Config.h"
#include "Code/Code.h"
#include "Code/Lexis.h"
#include "Statistics/Region.h"
#include "Frequency.hpp"

namespace code_learning {

	class SourceFile {
	
	public:
		explicit SourceFile(const char *fileName);
		void Scan(const Glob &glob);
		void Statistics(ListMap<Frequency<statistics::Region, statistics::Region>> &regions)const;
		
		std::unique_ptr<code::Code> m_code;
		std::string m_content;
		std::string m_file_name;
	};
}

#endif