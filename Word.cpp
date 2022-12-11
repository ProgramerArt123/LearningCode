#include "Config.h"
#include "Char.h"
#include "Word.h"

namespace code_learning {
	

	Word::Word(const std::string &content, const Config &cfg):
		AdjacencyWord(content, cfg), m_front(cfg), m_back(cfg){

	}
}