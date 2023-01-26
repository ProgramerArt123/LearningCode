#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include "Config.h"
#include "SourceFile.h"

namespace code_learning {
	namespace code {
		SourceFile::SourceFile(const char *fileName):
			Code(fileName){
			m_type = ELEMENT_TYPE_FILE;
			std::ifstream source(m_file_name);
			if (source.is_open()) {
				std::stringstream buffer;
				buffer << source.rdbuf();
				SetContent(buffer.str().c_str());
			}
			else {
				std::cerr << m_file_name << " open failed!" << std::endl;
			}
			m_file_count = 1;
		}
		

		
	}
}

