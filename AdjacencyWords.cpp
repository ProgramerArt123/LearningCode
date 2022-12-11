#include <iostream>
#include "Word.h"
#include "AdjacencyWords.h"

namespace code_learning {
	CountAdjacencyWords::CountAdjacencyWords(WORD_TYPE type, const Config &cfg):
		m_type(type), m_frequencies(cfg){

	}
	CountAdjacencyWords::CountAdjacencyWords(const CountAdjacencyWords& other) :
		m_type(other.m_type), m_frequencies(other.m_frequencies.m_cfg) {
	}
	AdjacencyWords::AdjacencyWords(const Config &cfg):
		m_cfg(cfg){

	}
	CountAdjacencyWords &AdjacencyWords::operator[](const std::string &content) {
		WORD_TYPE type = AdjacencyWord::JudgeWordType(content);
		for (auto &frequency : m_words) {
			if (frequency.m_type == type) {
				return frequency;
			}
		}
		m_words.push_back(CountAdjacencyWords(type, m_cfg));
		return m_words.back();
	}

	AdjacencyWord &AdjacencyWords::Count(const std::string &content) {
		CountAdjacencyWords &words = (*this)[content];
		words.m_frequencies[content]++;
		words.m_total_count++;
		return words.m_frequencies[content];
	}

	static bool compare(const CountAdjacencyWords &one, const CountAdjacencyWords &other) {
		return one.m_total_count > other.m_total_count;
	}
	void AdjacencyWords::Sort() {
		for (auto &word : m_words) {
			word.m_frequencies.Sort();
		}
		m_words.sort(compare);
	}
}