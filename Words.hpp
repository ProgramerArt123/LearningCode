#ifndef __CODE_LEARNING_WORDS_HPP__
#define __CODE_LEARNING_WORDS_HPP__

#include <memory>
#include <map>
#include <list>

namespace code_learning {
	
	class Config;

	template<typename WORD>
	class Words {
	public:
		Words(const Config &cfg) :
			m_cfg(cfg) {
		}
		typename std::list<std::shared_ptr<WORD>>::const_iterator begin() const {
			return m_words_list.begin();
		}
		typename std::list<std::shared_ptr<WORD>>::const_iterator end() const {
			return m_words_list.end();
		}
		WORD &operator[](const std::string &content) {
			if (m_words_map.end() == m_words_map.find(content)) {
				std::shared_ptr<WORD> word(new WORD(content, m_cfg));
				m_words_map.insert(std::make_pair(content, word));
				m_words_list.push_back(word);
			}
			return *m_words_map[content];
		}

		static bool compare(const std::shared_ptr<WORD> &one, const std::shared_ptr<WORD> &other) {
			return one->GetCount() > other->GetCount();
		}
		void Sort() {
			m_words_list.sort(compare);
			for (const auto &word : m_words_list) {
				word->Sort();
			}
		}
		const Config &m_cfg;
	private:
		std::map<std::string, std::shared_ptr<WORD>> m_words_map;
		std::list<std::shared_ptr<WORD>> m_words_list;
	};

}

#endif