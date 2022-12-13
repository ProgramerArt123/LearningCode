#ifndef __CODE_LEARNING_ADJACENCY_WORDS_H__
#define __CODE_LEARNING_ADJACENCY_WORDS_H__

#include <list>
#include <memory>

namespace code_learning {
	
	struct Config;
	class CountAdjacencyWords;

	class AdjacencyWords {
	public:
		explicit AdjacencyWords(const Config &cfg);
		CountAdjacencyWords &operator[](const std::string &content);
		AdjacencyWord &Count(const std::string &content);
		void Sort();
	private:
		std::list<std::shared_ptr<CountAdjacencyWords>> m_words;
		const Config &m_cfg;
	};

}

#endif