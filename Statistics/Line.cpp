#include <iostream>
#include "Code/Code.h"
#include "Lexis.h"
#include "Glob.h"
#include "Code/Line.h"
#include "Line.h"

namespace code_learning {
	namespace statistics {
		Line::Line(const std::string &content, Glob &glob) :
			Element(content, glob), m_words(glob) {
		}
		void Line::Statistics(code::Line &line) {
			m_signature = line.GetSignature();
			std::string preWord;
			for (auto lexis = line.begin(); lexis != line.end(); ) {
				if ((*lexis)->IsSpace()) {
					lexis++;
					continue;
				}

				std::string description;
				while ((*lexis)->IsMulti()) {
					description.append(std::string((*lexis)->begin(), (*lexis)->end()));
					if (++lexis == line.end()) {
						break;
					}
				}
				if (!description.empty()) {
					m_descs.AddDescription(description);
					if (lexis != line.end()) {
						m_glob.m_generate.wrappers.insert(Wrapper(preWord, std::string((*lexis)->begin(), (*lexis)->end())));
						lexis++;
					}
					else {
						m_glob.m_generate.wrappers.insert(Wrapper(preWord));
					}
					continue;
				}

				const Wrapper &wrapper = PeekWrap(lexis, line.end());
				if (!wrapper.m_prefix.empty()) {
					m_words[wrapper.m_prefix]++;
					if (!preWord.empty()) {
						m_words[wrapper.m_prefix].m_front.Count(preWord);
						m_words[preWord].m_back.Count(wrapper.m_prefix);
					}
					while (true) {
						description.append(std::string((*lexis)->begin(), (*lexis)->end()));
						lexis++;
						if (lexis == line.end()) {
							return;
						}
						if (PeekWrap(lexis, wrapper.m_suffix, line.end())) {
							m_descs.AddDescription(description);
							break;
						}
					}
					m_words[preWord = wrapper.m_suffix]++;
					continue;
				}

				const std::string lexisContent((*lexis)->begin(), (*lexis)->end());
				m_words[lexisContent]++;
				if (!preWord.empty()) {
					m_words[lexisContent].m_front.Count(preWord);
					m_words[preWord].m_back.Count(lexisContent);
				}
				preWord = lexisContent;
				lexis++;
			}
		}
		Wrapper Line::PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis, 
			std::list<std::unique_ptr<Lexis>>::const_iterator end) const {
			for (const auto &wrap : m_glob.m_generate.wrappers) {
				bool isMatching = true;
				auto cursor = lexis;
				for (const auto &c : wrap.m_prefix) {
					if (c != *(*cursor)->begin()) {
						isMatching = false;
						break;
					}
					cursor++;
					if (cursor == end) {
						return Wrapper();
					}
				}
				if (isMatching) {
					lexis = cursor;
					return wrap;
				}
			}
			return Wrapper();
		}
		bool Line::PeekWrap(std::list<std::unique_ptr<Lexis>>::const_iterator &lexis,
			const std::string &wrap, std::list<std::unique_ptr<Lexis>>::const_iterator end)const {
			bool isMatching = true;
			auto cursor = lexis;
			for (const auto &c : wrap) {
				if (cursor == end) {
					throw "SourceFile::PeekWrap";
				}
				if (c != *(*cursor)->begin()) {
					isMatching = false;
					break;
				}
				cursor++;
			}
			if (isMatching) {
				lexis = cursor;
				return true;
			}
			return false;
		}
		void Line::Summary()const {
			std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
			std::cout << "Line:" << std::endl;
			std::cout << "Key:" << m_signature << std::endl;
			std::cout << "Content:" << m_content << std::endl;
			std::cout << "Words:[";
			for (const auto &word : m_words) {
				std::cout << word->m_element.GetContent() << ':' << word->GetCount() << '\t';
			}
			std::cout << "]";
			std::cout << std::endl << "-------------------------------------------------" << std::endl;
			if (m_descs.begin() != m_descs.end()) {
				std::cout << "Descs:<";
				for (const auto &desc : m_descs) {
					std::cout << desc->m_content << std::endl;
				}
				std::cout << ">";
			}
			std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		}
	}
}