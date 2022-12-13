#include <iostream>
#include <algorithm>
#include "FrequencyWord.h"
#include "Lexis.h"
#include "SourceFile.h"
#include "CodeLearning.h"

namespace code_learning {

	CodeLearning::CodeLearning():m_frequencies(m_cfg) {

	}

	void CodeLearning::Learning(SourceFile &source) {
		source.Scan(m_cfg);
		m_file_count++;
		for (const auto &lexis : source) {
			const std::string lexisContent(lexis->begin(), lexis->end());
			m_frequencies[lexisContent]++;
		}
		auto preLexisItor = source.begin();
		for (auto lexisItor = source.begin();
			lexisItor != source.end(); lexisItor ++) {
			if (preLexisItor!=lexisItor) {
				const std::string preLexisContent((*preLexisItor)->begin(), (*preLexisItor)->end());
				const std::string lexisContent((*lexisItor)->begin(), (*lexisItor)->end());
				m_frequencies[preLexisContent].m_back.Count(lexisContent);
				m_frequencies[lexisContent].m_front.Count(preLexisContent);
			}
			preLexisItor = lexisItor;
		}
		m_frequencies.Sort();
	}
	
	void CodeLearning::Summary() {
		std::cout << "learn file[" << m_file_count << "]" << std::endl;
		std::cout << "learn lexis:" << std::endl;
		for (const auto &word : m_frequencies) {
			std::cout << word->GetContent() << ':' << word->GetCount() << '\t';
		}
		
	}
}