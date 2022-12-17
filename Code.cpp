#include <cstring>
#include <iostream>
#include "Config.h"
#include "Lexis.h"
#include "Code.h"

namespace code_learning {

	Code::Code(const char *content, const Config &cfg):m_cfg(cfg){
		std::cout << "代码学习" << std::endl;
		size_t len = strlen(content);
		bool isPreSplit = false;
		for (size_t index = 0; index < len; index ++) {
			if (CheckEncoding(content, len, index, isPreSplit)) {
				break;
			}
			if (CheckWrap(content, len, index, isPreSplit)) {
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

	bool Code::CheckEncoding(const char *content, size_t len, size_t &index, bool &isPreSplit) {
		uint8_t highOne = CharHighOne(content[index]);
		if (highOne) {
			m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis()));
		}
		while (highOne) { //描述性对象
			std::unique_ptr<Lexis> &last = m_lexes.back();
			for (uint8_t one = 0; one < highOne; one++) {
				last->AppendChar(content[index++]);
			}
			highOne = CharHighOne(content[index]);
			isPreSplit = true;
		}
		return index == len;
	}

	bool Code::CheckWrap(const char *content, size_t len, size_t &index, bool &isPreSplit) {
		for (const auto &wrap : m_cfg.wrappers) {
			if (len > index + wrap.m_prefix.length() &&
				wrap.m_prefix == std::string(content + index,
				wrap.m_prefix.length())) {
				m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis()));
				std::unique_ptr<Lexis> &prefix = m_lexes.back();
				for (uint8_t j = 0; j < wrap.m_prefix.length(); j++) {
					prefix->AppendChar(content[index++]);
				}
				m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis()));
				std::unique_ptr<Lexis> &desc = m_lexes.back();
				while (index + wrap.m_suffix.length() < len && wrap.m_suffix != std::string(content + index,
					wrap.m_suffix.length())) {
					desc->AppendChar(content[index++]);
				}
				desc->SetDesc();
				m_lexes.push_back(std::unique_ptr<Lexis>(new Lexis()));
				std::unique_ptr<Lexis> &suffix = m_lexes.back();
				for (uint8_t j = 0; j < wrap.m_suffix.length(); j++) {
					suffix->AppendChar(content[index++]);
				}
				break;
			}
		}
		return index == len;
	}
}