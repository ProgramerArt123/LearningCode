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
		std::string preWord;
		for (auto lexis = source.begin(); lexis != source.end(); ) {
			if ((*lexis)->IsSpace()) {
				lexis++;
				continue;
			}

			std::string description;
			while ((*lexis)->IsMulti()) {
				description += std::string((*lexis)->begin(), (*lexis)->end());
				lexis++;
			}
			if (!description.empty()) {
				m_descs.AddDescription(description);
				m_cfg.wrappers.insert(Wrapper(preWord, std::string((*lexis)->begin(), (*lexis)->end())));
				lexis++;
				continue;
			}

			const Wrapper &wrapper = source.PeekWrap(lexis, m_cfg);
			if (!wrapper.m_prefix.empty()) {
				m_frequencies[wrapper.m_prefix]++;
				if (!preWord.empty()) {
					m_frequencies[wrapper.m_prefix].m_front.Count(preWord);
					m_frequencies[preWord].m_back.Count(wrapper.m_prefix);
				}
				while (true){
					description += std::string((*lexis)->begin(), (*lexis)->end());
					lexis++;
					if (lexis == source.end()) {
						return;
					}
					if (source.PeekWrap(lexis, wrapper.m_suffix)) {
						m_descs.AddDescription(description);
						break;
					}
				}
				m_frequencies[preWord = wrapper.m_suffix]++;
				continue;
			}

			const std::string lexisContent((*lexis)->begin(), (*lexis)->end());
			m_frequencies[lexisContent]++;
			if (!preWord.empty()) {
				m_frequencies[lexisContent].m_front.Count(preWord);
				m_frequencies[preWord].m_back.Count(lexisContent);
			}
			preWord = lexisContent;
			lexis++;
		}
	}
}