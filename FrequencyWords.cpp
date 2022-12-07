#include <iostream>
#include "FrequencyWords.h"

namespace code_learning {
	Word::Word(const std::string &content):
		m_content(content){

	}
	Word &Word::operator++(int) {
		m_count++;
		return *this;
	}
	const std::string &Word::GetContent()const {
		return m_content;
	}
	uint64_t Word::GetCount()const {
		return m_count;
	}
	std::list<std::shared_ptr<Word>>::const_iterator FrequencyWords::begin() const {
		return m_words_list.begin();
	}
	std::list<std::shared_ptr<Word>>::const_iterator FrequencyWords::end() const {
		return m_words_list.end();
	}
	Word &FrequencyWords::operator[](const std::string &content) {
		if (m_words_map.end() == m_words_map.find(content)) {
			std::shared_ptr<Word> word(new Word(content));
			m_words_map.insert(std::make_pair(content, word));
			m_words_list.push_back(word);
		}
		return *m_words_map[content];
	}

	bool compare(const std::shared_ptr<Word> &one, const std::shared_ptr<Word> &other) {
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