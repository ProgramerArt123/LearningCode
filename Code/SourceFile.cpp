#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include "Config.h"
#include "SourceFile.h"

namespace code_learning {
	namespace code {
		SourceFile::SourceFile(const char *fileName):
			SourcePath(fileName){
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
			m_file_count = 1;
		}
		uint64_t SourceFile::Scan(const Glob &glob) {
			if (m_code)
				return m_code->Scan(glob);
			return 0;
		}
		void SourceFile::Foreach(std::function<void(const std::string &, const std::vector<std::list<std::shared_ptr<code::Element>>> &)> factor) const {
			if (m_code) {
				factor(m_file_name, m_code->m_children);
			}
		}
	}
}

