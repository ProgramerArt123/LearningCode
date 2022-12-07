#ifndef __CODE_LEARNING_FREQUENCY_WORDS_H__
#define __CODE_LEARNING_FREQUENCY_WORDS_H__

#include <memory>
#include <map>
#include <list>

namespace code_learning {
	
	class Word;

	class FrequencyWords {
	public:
		std::list<std::shared_ptr<Word>>::const_iterator begin() const;
		std::list<std::shared_ptr<Word>>::const_iterator end() const;
		Word &operator[](const std::string &content);
		void Sort();
	private:
		std::map<std::string, std::shared_ptr<Word>> m_words_map;
		std::list<std::shared_ptr<Word>> m_words_list;
	};

	class Word {
	public:
		explicit Word(const std::string &content);
		Word &operator++(int);
		const std::string &GetContent()const;
		uint64_t GetCount()const;
		FrequencyWords m_front;
		FrequencyWords m_back;
	private:
		const std::string m_content;
		uint64_t m_count = 0;
	};
}

#endif