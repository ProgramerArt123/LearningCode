#include <iostream>
#include "CodeLearning.h"

namespace code_learning {

	void CodeLearning::Learning(SourceFile &source) {
		source.Scan(m_cfg);
		m_file_count++;
		for (const auto &lexis : source) {
			m_lexes[std::string(lexis->begin(), lexis->end())]++;
		}
	}

	void CodeLearning::Summary() {
		std::cout << "learn file[" << m_file_count << "]" << std::endl;
		std::cout << "learn lexis:" << std::endl;
		for (const auto &lexis : m_lexes) {
			std::cout << lexis.first << ':' << lexis.second << '\t';
		}
	}
}