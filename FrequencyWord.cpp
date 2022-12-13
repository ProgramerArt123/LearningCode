#include "Config.h"
#include "Char.h"
#include "FrequencyWord.h"

namespace code_learning {
	
	FrequencyWord::FrequencyWord(const std::string &content, const Config &cfg):
		AdjacencyWord(content, cfg), m_front(cfg), m_back(cfg){

	}
	void FrequencyWord::Sort()  {
		m_front.Sort();
		m_back.Sort();
	}
}