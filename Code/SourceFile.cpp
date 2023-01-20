#include <fstream>
#include <sstream>
#include <iostream>
#include "Config.h"
#include "SourceFile.h"

namespace code_learning {
	namespace code {
		SourceFile::SourceFile(const char *fileName) :m_file_name(fileName) {
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
		uint64_t SourceFile::Scan(const Glob &glob) {
			if (m_code)
				m_code->Decomposition(glob);
			return 1;
		}
		void SourceFile::Foreach(std::function<void(const std::list<std::unique_ptr<code::Region>> &)> factor) const {
			if (m_code) {
				factor(m_code->m_regions);
			}
		}
	}
}

