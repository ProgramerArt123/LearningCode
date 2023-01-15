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
			m_code.reset(new code::Code(m_content.c_str()));
		}
		else {
			std::cerr << m_file_name << " open failed!" << std::endl;
		}
	}
	void SourceFile::Scan(const Glob &glob) {
		if (m_code)
			m_code->Decomposition(glob);
	}
	void SourceFile::Statistics(ListMap<Frequency<statistics::Region, statistics::Region>> &regions)const {
		if (m_code)
			m_code->Statistics(regions);
	}
}

