#include <iostream>
#include "Char.h"
#include "AdjacencyWord.h"

namespace code_learning {
	AdjacencyWord::AdjacencyWord(const std::string &content, const Config &cfg) :
		Word(content, cfg) {
	}
	AdjacencyWord &AdjacencyWord::operator++(int) {
		m_count++;
		return *this;
	}

	uint64_t AdjacencyWord::GetCount()const {
		return m_count;
	}

}