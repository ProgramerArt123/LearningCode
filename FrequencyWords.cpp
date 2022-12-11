#include <iostream>
#include "Word.h"
#include "FrequencyWords.h"

namespace code_learning {
	FrequencyWords::FrequencyWords(const Config &cfg):
		m_cfg(cfg){

	}
	std::list<std::shared_ptr<Word>>::const_iterator FrequencyWords::begin() const {
		return m_words_list.begin();
	}
	std::list<std::shared_ptr<Word>>::const_iterator FrequencyWords::end() const {
		return m_words_list.end();
	}
	Word &FrequencyWords::operator[](const std::string &content) {
		if (m_words_map.end() == m_words_map.find(content)) {
			std::shared_ptr<Word> word(new Word(content, m_cfg));
			m_words_map.insert(std::make_pair(content, word));
			m_words_list.push_back(word);
		}
		return *m_words_map[content];
	}

	static bool compare(const std::shared_ptr<Word> &one, const std::shared_ptr<Word> &other) {
		return one->GetCount() > other->GetCount();
	}
	void FrequencyWords::Sort() {
		m_words_list.sort(compare);
		for (const auto &word : m_words_list) {
			word->m_front.Sort();
			word->m_back.Sort();
		}
	}
}