#include <fstream>
#include <sstream>
#include <iostream>
#include "Config.h"
#include "SourceFile.h"

namespace code_learning {

	SourceFile::SourceFile(const char *fileName):m_file_name(fileName){
		std::ifstream source(m_file_name);
		if (source.is_open()) {
			std::stringstream buffer;
			buffer << source.rdbuf();
			m_content = buffer.str();
		}
		else {
			std::cerr << m_file_name << " open failed!" << std::endl;
		}
	}
	void SourceFile::Scan(Config &cfg) {
		m_code.reset(new code::Code(m_content.c_str(), cfg));
	}
	void SourceFile::Statistics(ListMap<Frequency<statistics::Region>> &regions)const {
		m_code->Statistics(regions);
	}
}

