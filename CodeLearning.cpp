#include <iostream>
#include <algorithm>
#include "FrequencyWord.h"
#include "Lexis.h"
#include "SourceFile.h"
#include "Description.h"
#include "CodeLearning.h"

namespace code_learning {

	CodeLearning::CodeLearning():m_frequencies(m_cfg), m_descs(m_cfg) {

	}

	void CodeLearning::Learning(SourceFile &source) {
		m_file_count++;
		source.Scan(m_cfg);
		StatisticsFrequencies(source);

		
		//auto preLexisItor = source.begin();
		//for (auto lexisItor = source.begin();
		//	lexisItor != source.end(); lexisItor ++) {
		//	if (preLexisItor!=lexisItor) {
		//		const std::string preLexisContent((*preLexisItor)->begin(), (*preLexisItor)->end());
		//		const std::string lexisContent((*lexisItor)->begin(), (*lexisItor)->end());
		//		if (!(*preLexisItor)->IsSpace()) {
		//			if (!(*preLexisItor)->IsDescription()) {
		//				m_frequencies[preLexisContent].m_back.Count(lexisContent);
		//			}
		//			else {
		//				Description &desc = m_descs.GetDescription(preLexisContent);
		//				desc.m_back = lexisContent;
		//				Wrapper desWrap(desc.m_front, desc.m_back);
		//				m_cfg.wrappers.insert(desWrap);
		//			}
		//		}

		//		if (!(*lexisItor)->IsSpace()) {
		//			if (!(*lexisItor)->IsDescription()) {
		//				m_frequencies[lexisContent].m_front.Count(preLexisContent);
		//			}
		//			else {
		//				Description &desc = m_descs.GetDescription(lexisContent);
		//				desc.m_front = preLexisContent;
		//			}
		//		}
		//	}
		//	preLexisItor = lexisItor;
		//}
		m_frequencies.Sort();
	}
	
	void CodeLearning::Summary() {
		std::cout << "learn file[" << m_file_count << "]" << std::endl;
		std::cout << "learn lexis:" << std::endl;
		for (const auto &word : m_frequencies) {
			std::cout << word->GetContent() << ':' << word->GetCount() << '\t';
		}
		std::cout << std::endl << "==================================================" << std::endl;
		for (const auto &desc : m_descs) {
			std::cout << desc->m_content << std::endl;
		}
	}

	void CodeLearning::StatisticsFrequencies(const SourceFile &source) {
		for (auto lexis = source.begin(); lexis != source.end(); ) {
			if ((*lexis)->IsSpace()) {
				lexis++;
				continue;
			}

			std::string description;

			uint8_t highOne = CharHighOne(*(*lexis)->begin());
			for (uint8_t index = 0; index < highOne; index++, lexis++) {
				description.push_back(*(*lexis)->begin());
			}
			if (!description.empty()) {
				m_descs.AddDescription(description);
				continue;
			}

			const std::string &prefix = source.PeekWrap(lexis, m_cfg);
			if (!prefix.empty()) {
				while (true){
					description.push_back(*(*lexis)->begin());
					lexis++;
					if (source.PeekWrap(lexis, prefix)) {
						m_descs.AddDescription(description);
						continue;
					}
				}
				continue;
			}

			const std::string lexisContent((*lexis)->begin(), (*lexis)->end());
			m_frequencies[lexisContent]++;
			lexis++;
		}
	}
}