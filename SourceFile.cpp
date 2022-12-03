#include <fstream>
#include <sstream>
#include "SourceFile.h"

namespace code_learning {

	SourceFile::SourceFile(const char *fileName) {
		std::ifstream source(fileName);
		if (source.is_open()) {
			std::stringstream buffer;
			buffer << source.rdbuf();
			m_content = buffer.str();
		}
	}
	void SourceFile::Scan(const Config &cfg) {
		m_code.reset(new Code(m_content.c_str(), cfg));
	}
	std::list<std::unique_ptr<Lexis>>::const_iterator SourceFile::begin() const {
		return m_code->GetLexes().begin();
	}
	std::list<std::unique_ptr<Lexis>>::const_iterator SourceFile::end() const {
		return m_code->GetLexes().end();
	}
}