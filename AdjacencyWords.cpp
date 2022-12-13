#include <iostream>
#include "CountAdjacencyWords.h"
#include "FrequencyWord.h"
#include "AdjacencyWords.h"

namespace code_learning {
	
	AdjacencyWords::AdjacencyWords(const Config &cfg):
		m_cfg(cfg){

	}
	CountAdjacencyWords &AdjacencyWords::operator[](const std::string &content) {
		WORD_TYPE type = AdjacencyWord::JudgeWordType(content);
		for (auto &frequency : m_words) {
			if (frequency->m_type == type) {
				return *frequency;
			}
		}
		m_words.push_back(std::shared_ptr<CountAdjacencyWords>(new CountAdjacencyWords(type, m_cfg)));
		return *m_words.back();
	}

	AdjacencyWord &AdjacencyWords::Count(const std::string &content) {
		CountAdjacencyWords &words = (*this)[content];
		words.m_adjacencies[content]++;
		words.m_total_count++;
		return words.m_adjacencies[content];
	}

	static bool compare(const std::shared_ptr<CountAdjacencyWords> &one, const std::shared_ptr<CountAdjacencyWords> &other) {
		return one->m_total_count > other->m_total_count;
	}
	void AdjacencyWords::Sort() {
		for (auto &word : m_words) {
			word->m_adjacencies.Sort();
		}
		m_words.sort(compare);
	}
}