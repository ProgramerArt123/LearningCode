#include <cstring>
#include <iostream>
#include "Glob.h"
#include "Lexis.h"
#include "Statistics/Lexis.h"
#include "Char.h"
#include "Block.h"

namespace code_learning {
	namespace code {
		Block::Block(char first):m_wrapper(first){
		}
		ELEMENT_TYPE Block::GetType() const {
			return ELEMENT_TYPE_BLOCK;
		}
		void Block::Decomposition(const Glob &glob) {
			size_t length = m_content.length();
			bool isPreSplit = false;
			for (size_t index = 0; index < length; index++) {
				isPreSplit = CheckEncoding(m_content.c_str(), index, glob);
				if (index == length) {
					break;
				}
				char c = m_content[index];
				if (!isPreSplit && !m_children.front().empty()) {
					std::shared_ptr<Element> &last = m_children.front().back();
					if (!last->TryAppendChar(c, glob)) {
						if (ELEMENT_TYPE_BLOCK == last->GetType()) {
							continue;
						}
						else if(glob.m_generate.symmetries.find(c) == 
							glob.m_generate.symmetries.end()){
							m_children.front().push_back(std::shared_ptr<Element>(new Lexis(c)));
						}
						else {
							m_children.front().push_back(std::shared_ptr<Element>(new Block(c)));
						}
					}
				}
				else {
					if (glob.m_generate.symmetries.find(c) ==
						glob.m_generate.symmetries.end()) {
						m_children.front().push_back(std::shared_ptr<Element>(new Lexis(c)));
					}
					else {
						m_children.front().push_back(std::shared_ptr<Element>(new Block(c)));
					}
				}
				isPreSplit = glob.m_cfg.splits.end() != glob.m_cfg.splits.find(c);
			}
			Composite<Element>::Decomposition(glob);
		}
		bool Block::ContentAppend(char next, const Glob &glob) {
			m_content += next;
			return false;
		}
		std::string Block::GetPattern(const Glob &glob) const {
			std::string pattern;
			pattern.append("[");
			for (const auto &lexis : m_children.front()) {
				LEXIS_TYPE type = statistics::Lexis::JudgeLexisType(std::string(lexis->begin(), lexis->end()));
				if (code_learning::LEXIS_TYPE_SPACE != type) {
					if (1 < pattern.length()) {
						pattern.append(",");
					}
					pattern.append(lexisTypes[type].m_name);
				}
			}
			pattern.append("]");
			return pattern;
		}
		bool Block::CheckEncoding(const char *content, size_t &index, const Glob &glob) {
			uint8_t highOne = CharHighOne(content[index]);
			bool isMulti = highOne;
			if (highOne) {//描述性对象
				m_children.front().push_back(std::shared_ptr<Element>(new Lexis()));
				std::shared_ptr<Element> &last = m_children.front().back();
				for (uint8_t one = 0; one < highOne; one++) {
					last->ContentAppend(content[index++], glob);
				}
			}
			return isMulti;
		}
		bool Block::TryAppendChar(char next, const Glob &glob) {
			if (glob.m_generate.symmetries.find(m_wrapper) ==
				glob.m_generate.symmetries.end()) {
				ContentAppend(next, glob);
				return false;
			}

			if (glob.m_generate.symmetries.at(m_wrapper).m_right == next) {
				return false;
			}
			else {
				ContentAppend(next, glob);
				return true;
			}
		}
	}
}