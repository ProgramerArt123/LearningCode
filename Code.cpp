#include <cstring>
#include <iostream>
#include "Config.h"
#include "Lexis.h"
#include "Code.h"

namespace code_learning {

	Code::Code(const char *content, const Config &cfg):m_cfg(cfg){
		"代码学习";
		size_t len = strlen(content);
		bool isPreSplit = false;
		for (size_t index = 0; index < len; index ++) {
			isPreSplit = CheckEncoding(content, index);
			if (index == len) {
				break;
			}
			char c = content[index];
			if (!isPreSplit && !m_lexes.empty()) {
				std::unique_ptr<Lexis> &last = m_lexes.back();
				if (!last->TryAppendChar(c)) {
					m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis(c)));
				}
			}
			else {
				m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis(c)));
			}
			isPreSplit = cfg.splits.end() != cfg.splits.find(c);
		}
	}

	const std::list<std::unique_ptr<Lexis>> &Code::GetLexes() const {
		return m_lexes;
	}

	bool Code::CheckEncoding(const char *content, size_t &index) {
		uint8_t highOne = CharHighOne(content[index]);
		bool isMulti = highOne;
		if (highOne) {
			m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis()));
		}
		while (highOne) { //描述性对象
			std::unique_ptr<Lexis> &last = m_lexes.back();
			for (uint8_t one = 0; one < highOne; one++) {
				last->AppendChar(content[index++]);
			}
			highOne = CharHighOne(content[index]);
		}
		return isMulti;
	}

}