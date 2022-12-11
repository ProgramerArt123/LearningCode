#ifndef __CODE_LEARNING_FREQUENCY_WORDS_H__
#define __CODE_LEARNING_FREQUENCY_WORDS_H__

#include <memory>
#include <map>
#include <list>

namespace code_learning {
	
	class Word;
	struct Config;

	class FrequencyWords {
	public:
		explicit FrequencyWords(const Config &cfg);
		std::list<std::shared_ptr<Word>>::const_iterator begin() const;
		std::list<std::shared_ptr<Word>>::const_iterator end() const;
		Word &operator[](const std::string &content);
		void Sort();
		const Config &m_cfg;
	private:
		std::map<std::string, std::shared_ptr<Word>> m_words_map;
		std::list<std::shared_ptr<Word>> m_words_list;
	};

}

#endif